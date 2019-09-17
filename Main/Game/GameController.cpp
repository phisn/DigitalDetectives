#include "GameController.h"

// #include "../Device/FaultHandler.h"

namespace Extern
{
	const unsigned long SectorGameSize = sizeof(Game::GameSector);
}

namespace
{
	Game::GameSector sector;

	FlashString lcd_ask_restore_1 = DEVICE_LCD_MESSAGE("Old session found, ");
	FlashString lcd_ask_restore_2 = DEVICE_LCD_MESSAGE("restore?           ");

	FlashString fault_sector_corrupted = DEVICE_FAULT_MESSAGE("Game Sector is corrupted      ");
	FlashString fault_invalid_state = DEVICE_FAULT_MESSAGE("Game was left in invalid state");
}

namespace Game
{
	namespace Controller
	{
		void StartSession();
		void RestoreSession();
		bool AskRestore();

		void Initialize()
		{
			Device::MemoryManager::ReadSector(
				Device::MemorySector::Game,
				(char*) &sector
			);
			
			switch (sector.state)
			{
			case State::Running:
				RestoreSession();

				break;
			default:
				Device::FaultHandler::Handle(
					{
						Device::FaultModule::GameController,
						(Device::FailureId) FID::INVALID_STATE + (int)sector.state,
						fault_invalid_state
					}, false);

				// fall through
			case State::Shutdown:
				StartSession();

				break;
			}
		}

		void Uninitialize()
		{
		}

		void StartSession()
		{
		}

		void RestoreSession()
		{
			if (!AskRestore())
			{
				StartSession();

				return;
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
