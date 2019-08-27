#include "MemoryManager.h"

namespace
{
	const size_t zone_offsets[] PROGMEM =
	{
		ZONE_MEMORY_STATUS,
		ZONE_MEMORY_FAULTHANDLER,
		ZONE_MEMORY_GAMESTATE
	};
}

namespace Device
{
	namespace MemoryManager
	{
		void Initialize()
		{
		}

		void Unintialize()
		{
		}

		void ReadMemoryZone(
			const MemoryZone zone, 
			char* const buffer)
		{
		}

		void WriteMemoryZone(
			const MemoryZone zone, 
			char* const buffer)
		{
		}

		void* AllocateDynamic(const size_t length)
		{
		}
	}
}