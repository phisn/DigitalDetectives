#pragma once

#define ZONE_MEMORY_STATUS_SIZE 0
#define ZONE_MEMORY_FAULTHANDLER_SIZE 0
#define ZONE_MEMORY_GAMESTATE_SIZE 0

#define ZONE_MEMORY_BEGIN 0
#define ZONE_MEMORY_STATUS ZONE_MEMORY_BEGIN
#define ZONE_MEMORY_FAULTHANDLER \
	ZONE_MEMORY_STATUS + ZONE_MEMORY_STATUS_SIZE
#define ZONE_MEMORY_GAMESTATE \
	ZONE_MEMORY_FAULTHANDLER + ZONE_MEMORY_FAULTHANDLER_SIZE

namespace Device
{
	enum class MemoryZone : unsigned char
	{
		FaultHandler,
		GameState
	};

	namespace MemoryManager
	{
		void Initialize();
		void Unintialize();

		void ReadMemoryZone(
			const MemoryZone zone,
			char* const buffer);
		void WriteMemoryZone(
			const MemoryZone zone,
			char* const buffer);

		void* AllocateDynamic(const size_t length);
	}
}
