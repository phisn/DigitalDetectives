#pragma once

#include "../Device/MemoryManager.h"
#include "../Game/BoardManager.h"

#pragma pack(push, 1)

namespace Game
{
	/*struct Sector
	{
		unsigned char check; // prevent use of corrupted data
		Game::Data data;
	};*/

	struct GameData
	{
		Player player[6];

		struct State
		{
		} state;
	};

	namespace Manager
	{
		struct FID
		{
			enum
			{
				SECTOR_CORRUPTED = 2
			};
		};

		void Begin(GameData* const gameData);
		// TODO: restore in game cant fail?
		void Restore(GameData* const gameData);
	}
}

#pragma pack(pop)
