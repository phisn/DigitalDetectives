#include "MemoryManager.h"

namespace Extern
{
	const unsigned long SectorFaultSize = 0;
	const unsigned long SectorValidationSize = sizeof(Device::ValidationSector);
}

namespace EOBJ
{
	extern EEPROMClass* EEPROM;
}

#define DEVICE_SECTOR_CHECK_OFFSET 0
#define DEVICE_SECTOR_FAULT_OFFSET Extern::SectorValidationSize
#define DEVICE_SECTOR_GAME_OFFSET Extern::SectorFaultSize + DEVICE_SECTOR_FAULT_OFFSET
#define DEVICE_SECTOR_EMPTY_OFFSET Extern::SectorGameSize + DEVICE_SECTOR_GAME_OFFSET

#define DEVICE_EEPROM_SIZE 512
#define DEVICE_EERPOM_SIZE_RUNTIME DEVICE_SECTOR_EMPTY_OFFSET

/*
	static_assert(DEVICE_EEPROM_SIZE > DEVICE_SECTOR_EMPTY_OFFSET,
		"Whole sector size cant be over DEVICE_EEPROM_SIZE");
*/

static_assert((int) Device::MemorySector::Validation == 0, "MemorySector order changed, adjust sector arrays");
static_assert((int) Device::MemorySector::Fault == 1, "MemorySector order changed, adjust sector arrays");
static_assert((int) Device::MemorySector::Game == 2, "MemorySector order changed, adjust sector arrays");

namespace
{
	unsigned long sector_offset[(int) Device::MemorySector::_Length] =
	{
		DEVICE_SECTOR_CHECK_OFFSET,
		DEVICE_SECTOR_FAULT_OFFSET,
		DEVICE_SECTOR_GAME_OFFSET
	};

	unsigned long sector_size[(int) Device::MemorySector::_Length] =
	{
		Extern::SectorValidationSize,
		Extern::SectorFaultSize,
		Extern::SectorGameSize
	};
}

namespace Device
{
	namespace MemoryManager
	{
		bool ValidateEEPROM();
		ValidationSector CreateValidation();
		void SignEEPROM();
		
		void Initialize()
		{
			if (DEVICE_EEPROM_SIZE < DEVICE_EERPOM_SIZE_RUNTIME)
			{
				Device::FailureHandler::Handle(
					FailureModule::MemoryManager,
					FID::EEPROM_OVERFLOW
				);
			}

			Serial.print("A.....");
			EOBJ::EEPROM->begin(DEVICE_EERPOM_SIZE_RUNTIME + 1);
			Serial.print("B.....");

			if (!ValidateEEPROM())
			{
				FailureHandler::Handle(
					FailureModule::MemoryManager,
					FID::EEPROM_CORRUPTED
				);
			}
		}

		void Unintialize()
		{
			// EEPROM.end();
		}

		void ReadSector(
			const MemorySector zone, 
			char* const buffer)
		{
			if ((int) zone > (int)MemorySector::_Length)
			{
				FailureHandler::Handle(
					FailureModule::MemoryManager,
					FID::INVALID_SECTOR
				);
			}

			const unsigned long size = sector_size[(int)zone];
			const unsigned long address = sector_offset[(int) zone];
			
			for (int i = 0; i < size; ++i)
			{
				buffer[i] = EOBJ::EEPROM->read(address + i);
			}
		}

		void WriteSector(
			const MemorySector sector,
			char* const buffer)
		{
			if ((int) sector > (int) MemorySector::_Length)
			{
				FailureHandler::Handle(
					FailureModule::MemoryManager,
					FID::INVALID_SECTOR
				);
			}

			const unsigned long size = sector_size[(int) sector];
			const unsigned long address = sector_offset[(int) sector];

			for (int i = 0; i < size; ++i)
			{
				EOBJ::EEPROM->write(address + i, buffer[i]);
			}

			if (!EOBJ::EEPROM->commit())
			{
				// possible failure -> invalid zone 
				// would result in infinit error code

				FailureHandler::Handle(
					Device::FailureModule::MemoryManager,
					FID::EEPROM_WRITE + (int) sector
				);
			}

			if (sector != MemorySector::Validation)
			{
				SignEEPROM();
			}
		}

		void CleanEEPROM()
		{
			for (int i = 0; i < DEVICE_EERPOM_SIZE_RUNTIME; ++i)
			{
				EOBJ::EEPROM->write(i, 0);
			}

			if (!EEPROM.commit())
			{
				FailureHandler::Handle(
					FailureModule::MemoryManager,
					FID::EEPROM_WRITE_CLEAN
				);
			}

			SignEEPROM();
		}

		void* AllocateDynamic(const unsigned long length)
		{
			if (ESP.getMaxFreeBlockSize() < length)
			{
				FailureHandler::Handle(
					FailureModule::MemoryManager,
					FID::HEAP_OVERFLOW
				);
			}

			return malloc(length);
		}

		void DeallocateDynamic(void* memory)
		{
			free(memory);
		}

		bool ValidateEEPROM()
		{
			ValidationSector checkSector;

			ReadSector(
				MemorySector::Validation,
				(char*) &checkSector
			);

			return checkSector == CreateValidation();
		}

		ValidationSector CreateValidation()
		{
			unsigned char result = 0;

			for (int i = 0; i < DEVICE_EERPOM_SIZE_RUNTIME; ++i)
			{
				// localData is not in progmem
				result += (EOBJ::EEPROM->read(DEVICE_SECTOR_CHECK_OFFSET + i)
					? + 1 
					: - 1) * (i % (1 >> 4));
			}

			return result;
		}

		void SignEEPROM()
		{
			ValidationSector validation = CreateValidation();

			WriteSector(
				MemorySector::Validation,
				(char*) &validation
			);
		}
	}
}