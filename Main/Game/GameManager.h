#pragma once

#include "../Device/MemoryManager.h"

#include "../Game/BoardManager.h"
#include "../Game/Player.h"

#pragma pack(push, 1)

namespace Game
{
	struct GameData
	{
		Player player[6];

		struct GameState
		{
		} state;
	};

	namespace GameManager
	{
		struct FID
		{
			enum
			{
				SECTOR_CORRUPTED = 2
			};
		};

		void Create();
		bool Process();
		void Restore();
	}
}

#pragma pack(pop)
