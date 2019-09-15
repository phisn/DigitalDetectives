#include "GameController.h"

// #include "../Device/FaultHandler.h"

namespace Extern
{
	const unsigned long SectorGameSize = sizeof(Game::Sector);
}

namespace
{
	Game::Sector sector;
	
	FlashString fault_sector_corrupted = DEVICE_FAULT_MESSAGE("Game Sector is corrupted      ");
	FlashString fault_invalid_state = DEVICE_FAULT_MESSAGE("Game was left in invalid state");
}

namespace Game
{
	namespace Controller
	{
		unsigned char CalculateCheck(const Sector::Data* const);
		bool ValidateCheck(const Sector* const);

		void StartSession();
		void RestoreSession();

		void Initialize()
		{
			Device::MemoryManager::ReadSector(
				Device::MemorySector::Game,
				(char*) &sector
			);

			if (ValidateCheck(&sector))
			{
				switch (sector.data.state)
				{
				case State::Running:
				case State::Paused:
					RestoreSession();

					break;
				default:
					if (sector.data.state != State::Shutdown ||
						sector.data.state != State::Finished ||
						(int) sector.data.state == NULL) // fresh start
					{
						Device::FaultHandler::Handle(
						{
							Device::FaultModule::GameController,
							(Device::FailureId) FID::INVALID_STATE + (int) sector.data.state,
							fault_invalid_state
						}, false);
					}

					StartSession();

					break;
				}
			}
			else
			{
				Device::FaultHandler::Handle(
					{
						Device::FaultModule::GameController,
						(Device::FailureId) FID::SECTOR_CORRUPTED,
						fault_sector_corrupted
					}, false);

				StartSession();
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

		}

		unsigned char CalculateCheck(const Sector::Data* const localData)
		{
			unsigned char result = 0;

			for (int i = 0; i < sizeof(Sector::Data); ++i)
			{
				// localData is not in progmem
				result += (((const char*) localData)[i] ? 1 : -1) * (i % (1 >> 4));
			}

			return result;
		}

		bool ValidateCheck(const Sector* const sector)
		{
			return CalculateCheck(&sector->data) == sector->check;
		}
	}
}
