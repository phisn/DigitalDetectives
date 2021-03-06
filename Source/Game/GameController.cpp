#include "GameController.h"

// #include "../Device/FaultHandler.h"

namespace Extern
{
	const unsigned long SectorGameSize = sizeof(Game::GameSector);

	Game::GameData* gameData;
	Game::SetupData* setupData;
	Game::CollectData* collectData;
}

namespace
{
	Game::GameSector sector;

	FlashString lcd_ask_restore_0 = DEVICE_LCD_MESSAGE("Old session found,  ");
	FlashString lcd_ask_restore_1 = DEVICE_LCD_MESSAGE("restore?            ");

	FlashString lcd_ask_restore_ensure_0 = DEVICE_LCD_MESSAGE("Are you sure you do ");
	FlashString lcd_ask_restore_ensure_1 = DEVICE_LCD_MESSAGE("not want to restore ");
	FlashString lcd_ask_restore_ensure_2 = DEVICE_LCD_MESSAGE("the old session?    ");

	FlashString fault_sector_corrupted = DEVICE_FAULT_MESSAGE("Game Sector is corrupted         ");
	FlashString fault_invalid_state = DEVICE_FAULT_MESSAGE("Game was left in an invalid state ");
	FlashString fault_invalid_running_state = DEVICE_FAULT_MESSAGE("Got invalid running state        ");
	FlashString fault_invalid_finish = DEVICE_FAULT_MESSAGE("Got invalid finish request       ");

	bool restored = false;
	bool requestFinish = false;
}

namespace Game
{
	namespace Controller
	{
		bool ProcessModules();
		void Save();

		void StartSession();
		void RestoreSession();
		bool AskRestore();

		bool FinishState();

		void Initialize()
		{
			// provide data to modules
			Extern::gameData = &sector.game;
			Extern::setupData = &sector.setup;
			Extern::collectData = &sector.collect;
			
			// restore or start
			Device::MemoryManager::ReadSector(
				Device::MemorySector::Game,
				(char*) &sector
			);
			
			switch (sector.state)
			{
			case GameState::Running:
				DEBUG_MESSAGE("Found old session, asking for restore");

				if (AskRestore())
				{
					RestoreSession();
					return;
				}

				break;
			default:
				Device::FaultHandler::Handle(
				{
					Device::FaultModule::GameController,
					(Device::FailureId) FID::INVALID_STATE + (int) sector.state,
					fault_invalid_state
				}, false);

				break;
			case GameState::Shutdown:
				DEBUG_MESSAGE("Found shutdown, continuing normally");

				break;
			}

			StartSession();
			Save();
		}

		void Save()
		{
			DEBUG_MESSAGE("Saving current session");

			Device::MemoryManager::WriteSector(
				Device::MemorySector::Game,
				(char*)& sector
			);

			DEBUG_MESSAGE("Current Session Saved");
		}

		void Uninitialize()
		{
		}

		bool Process()
		{
			if (requestFinish)
			{
				requestFinish = false;

				if (FinishState())
				{
					BoardManager::OnStateChanged(sector.state);

					return false;
				}
			}

			bool result = ProcessModules();

			if (result)
			{
				Save();
				BoardManager::Update();
			}

			BoardManager::Process();

			return result;
		}

		GameState GetState()
		{
			return sector.state;
		}

		bool ProcessModules()
		{
			switch (sector.state)
			{
			case GameState::Collect:
				return Collector::Process();

			case GameState::Running:
				return GameManager::Process();

			case GameState::Setup:
				return SetupManager::Process();

			default:
				Device::FaultHandler::Handle(
					{
						Device::FaultModule::GameController,
						(int) FID::INVALID_STATE_RUNNING + (int) sector.state,
						fault_invalid_running_state
					}, true);

				break;
			}

			return false; // unreachable
		}

		void StartSession()
		{
			DEBUG_MESSAGE("Starting session");

			sector.state = GameState::Collect;
			Collector::Create();
			BoardManager::OnStateChanged(GameState::Collect);
		}

		void RestoreSession()
		{
			DEBUG_MESSAGE("Restoring session");

			Collector::Restore();
			SetupManager::Restore();
			GameManager::Restore();

			BoardManager::OnStateChanged(GameState::Running);

			restored = true;
			DEBUG_MESSAGE("Session restored");
		}

		bool AskRestore()
		{
			Device::OutputManager::Lcd::Clear();

			Device::OutputManager::Lcd::DisplayLineType(0, lcd_ask_restore_0);
			Device::OutputManager::Lcd::DisplayLineType(1, lcd_ask_restore_1);
			Device::OutputManager::Lcd::DisplayLineType(3, Device::OutputManager::Interact::GetCommonYesNo());
			
			if (Device::OutputManager::Interact::ForceGetChoice() 
				== Device::OutputManager::Interact::Choice::Yes)
			{
				return true;
			}
			else
			{
				// no refresh needed
				Device::OutputManager::Lcd::DisplayLineType(0, lcd_ask_restore_ensure_0);
				Device::OutputManager::Lcd::DisplayLineType(1, lcd_ask_restore_ensure_1);
				Device::OutputManager::Lcd::DisplayLineType(2, lcd_ask_restore_ensure_2);

				Device::OutputManager::Lcd::DisplayLineType(3, Device::OutputManager::Interact::GetCommonYesNo());

				// important delay to prevent accidental press3
				delay(1000);

				return Device::OutputManager::Interact::ForceGetChoice()
					== Device::OutputManager::Interact::Choice::No;
			}
		}

		bool FinishState()
		{
			switch (sector.state)
			{
			case GameState::Collect:
				if (Collector::Finish())
				{
					DEBUG_MESSAGE("Finishing Collect, starting setup");

					sector.state = GameState::Setup;
					SetupManager::Create();

					return true;
				}

				break;
			case GameState::Setup:
				if (SetupManager::Finish())
				{
					DEBUG_MESSAGE("Finishing Setup, starting running");

					sector.state = GameState::Running;
					GameManager::Create();

					return true;
				}

				break;
			case GameState::Running:
				if (SetupManager::Finish())
				{

					DEBUG_MESSAGE("Finishing Running, starting finish");

					sector.state = GameState::Finish;
					FinishManager::Create();

					return true;
				}

				break;
			default:
				Device::FaultHandler::Handle(
				{
					Device::FaultModule::GameController,
					(Device::FailureId) FID::INVALID_FINISH,
					fault_invalid_finish
				}, false);

				break;
			}

			DEBUG_MESSAGE("Finish canceled");

			return false;
		}

		void RequestFinish()
		{
			DEBUG_MESSAGE("Finish requested");
			requestFinish = true;
		}

		bool IsRestored()
		{
			return restored;
		}
	}
}
