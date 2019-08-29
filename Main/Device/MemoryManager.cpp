#include "MemoryManager.h"

namespace
{
	unsigned long zone_offsets[3] =
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

		void* AllocateDynamic(const unsigned long length)
		{
		}
	}
}