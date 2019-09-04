#pragma once

#include "../Device/FailureHandler.h"

extern const unsigned long SectorBootSize;
extern const unsigned long SectorFaultSize;
extern const unsigned long SectorGameSize;

namespace Device
{
	enum class MemorySector : unsigned char
	{
		Boot,
		Fault,
		Game,

		_Length
	};

	namespace MemoryManager
	{
		struct FID
		{
			enum
			{
				EEPROM_WRITE = 2 // -> + MemorySector::_Length
			};
		};

		void Initialize();
		void Unintialize();

		void ReadSector(
			const MemorySector zone,
			char* const buffer);
		void WriteSector(
			const MemorySector zone,
			char* const buffer);

		void* AllocateDynamic(const unsigned long length);
		void DeallocateDynamic(void* memory);
	}
}
