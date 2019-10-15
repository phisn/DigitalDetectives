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

	FlashString lcd_ask_restore_1 = DEVICE_LCD_MESSAGE("Old session found,  ");
	FlashString lcd_ask_restore_2 = DEVICE_LCD_MESSAGE("restore?            ");

	FlashString fault_sector_corrupted = DEVICE_FAULT_MESSAGE("Game Sector is corrupted      ");
	FlashString fault_invalid_state = DEVICE_FAULT_MESSAGE("Game was left in invalid state");
	FlashString fault_invalid_running_state = DEVICE_FAULT_MESSAGE("Got invalid running state     ");

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
				RestoreSession();

				break;
			default:
				Device::FaultHandler::Handle(
					{
						Device::FaultModule::GameController,
						(Device::FailureId) FID::INVALID_STATE + (int)sector.state,
						fault_invalid_state
					}, false);

			case GameState::Shutdown:
				break;
			}

			StartSession();
			Save();
		}

		void Save()
		{
			Device::MemoryManager::WriteSector(
				Device::MemorySector::Game,
				(char*)& sector
			);
		}

		void Uninitialize()
		{
		}

		bool Process()
		{
			bool result = ProcessModules();

			if (result)
			{
				Save();
				BoardManager::Update();
			}

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
						(int)sector.state,
						fault_invalid_running_state
					}, true);

				break;
			}

			return false; // unreachable
		}

		void StartSession()
		{
			sector.state = GameState::Collect;
		}

		void RestoreSession()
		{
			if (AskRestore())
			{
				Collector::Restore();
				SetupManager::Restore();
				GameManager::Restore();
			}
		}

		bool AskRestore()
		{
			Device::OutputManager::Lcd::DisplayLineType(1, lcd_ask_restore_1);
			Device::OutputManager::Lcd::DisplayLineType(2, lcd_ask_restore_2);

			Device::OutputManager::Lcd::Clear();

			return Device::OutputManager::Interact::ForceGetChoice()
				== Device::OutputManager::Interact::Choice::Yes;
		}
	}
}
