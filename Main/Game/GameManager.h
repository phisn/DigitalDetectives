#pragma once

#include "../Device/MemoryManager.h"
#include "../Game/BoardManager.h"

namespace Game
{
	struct Sector
	{
		unsigned char check;
		Game::Data data;
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

		void Initialize();
		void Uninitialize();

		void Create();
		void Restore();
	}
}
