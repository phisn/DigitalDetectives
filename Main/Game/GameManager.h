#pragma once

#include "../Device/MemoryManager.h"

#include "../Game/BoardManager.h"
#include "../Game/Data/GameData.h"

#pragma pack(push, 1)

namespace Game
{
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
