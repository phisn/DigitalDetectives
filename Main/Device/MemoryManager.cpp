#include "MemoryManager.h"

const unsigned long SectorBootSize = 0;
const unsigned long SectorFaultSize = 0;
const unsigned long SectorGameSize = 0;

#define DEVICE_SECTOR_BOOT_OFFSET 0
#define DEVICE_SECTOR_FAULT_OFFSET SectorBootSize
#define DEVICE_SECTOR_GAME_OFFSET SectorFaultSize + DEVICE_SECTOR_FAULT_OFFSET
#define DEVICE_SECTOR_EMPTY_OFFSET SectorGameSize + DEVICE_SECTOR_GAME_OFFSET

#define DEVICE_EEPROM_SIZE 512

/*
	static_assert(DEVICE_EEPROM_SIZE > DEVICE_SECTOR_EMPTY_OFFSET,
		"Whole sector size cant be over DEVICE_EEPROM_SIZE");
*/

namespace
{
	unsigned long sector_offset[(int) Device::MemorySector::_Length] =
	{
		DEVICE_SECTOR_BOOT_OFFSET,
		DEVICE_SECTOR_FAULT_OFFSET,
		DEVICE_SECTOR_GAME_OFFSET
	};

	unsigned long sector_size[(int) Device::MemorySector::_Length] =
	{
		SectorBootSize,
		SectorFaultSize,
		SectorGameSize
	};
}

namespace Device
{
	namespace MemoryManager
	{
		void Initialize()
		{
			EEPROM.begin(DEVICE_SECTOR_EMPTY_OFFSET + 1);
		}

		void Unintialize()
		{
			// EEPROM.end();
		}

		void ReadSector(
			const MemorySector zone, 
			char* const buffer)
		{
			const unsigned long size = sector_size[(int)zone];
			const unsigned long address = sector_offset[(int) zone];
			
			for (int i = 0; i < size; ++i)
			{
				buffer[i] = EEPROM.read(address + i);
			}
		}

		void WriteSector(
			const MemorySector zone,
			char* const buffer)
		{
			const unsigned long size = sector_size[(int)zone];
			const unsigned long address = sector_offset[(int)zone];

			for (int i = 0; i < size; ++i)
			{
				EEPROM.write(address + i, buffer[i]);
			}

			if (!EEPROM.commit())
			{
				// possible failure -> invalid zone 
				// would result in infinit error code

				FailureHandler::Handle(
					Device::FailureModule::MemoryManager,
					FID::EEPROM_WRITE + (int) zone
				);
			}
		}

		void* AllocateDynamic(const unsigned long length)
		{
			return malloc(length);
		}

		void DeallocateDynamic(void* memory)
		{
			free(memory);
		}
	}
}