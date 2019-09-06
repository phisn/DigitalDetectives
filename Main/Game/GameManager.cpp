#include "GameManager.h"

const unsigned long SectorGameSize = sizeof(Game::Sector);

namespace
{
	Game::Data data;

	FlashString fault_sector_corrupted = DEVICE_FAULT_MESSAGE("Game Sector is corrupted      ");
}

namespace Game
{
	// from GameData.h
	const Data* GetData()
	{
		return &data;
	}

	namespace Manager
	{
		unsigned char CalculateCheck(const Data* const);
		bool ValidateCheck(const Data* const);

		void Initialize()
		{
		}

		void Create()
		{
		}

		void Restore()
		{
			Sector sectorBuffer;

			Device::MemoryManager::ReadSector(
				Device::MemorySector::Game,
				(char*) &sectorBuffer
			);

			if (ValidateCheck(&sectorBuffer))
			{
				memcpy(&data, &sectorBuffer.data, sizeof(Data));
			}
			else
			{
				Device::FaultHandler::Handle(
				{
					Device::FaultModule::GameManager,
					(Device::FailureId) FID::SECTOR_CORRUPTED,
					fault_sector_corrupted
				}, false); // not fatal, can continue

				Create();
			}
		}
		
		unsigned char CalculateCheck(const Data* const localData)
		{
			unsigned char result = 0;

			for (int i = 0; i < sizeof(Data); ++i)
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
