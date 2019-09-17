#pragma once

#include "../Game/Collector.h"
#include "../Game/GameManager.h"
#include "../Game/SetupManager.h"

namespace Game
{
	enum class State : unsigned char
	{
		Shutdown = 0, // zero for fresh start / clean
		Running,

		Setup,
		Collect,
		Restore
	};

	struct GameSector
	{
		GameData game;
		SetupData setup;
		CollectData collect;

		State state;
	};

	namespace Controller
	{
		struct FID
		{
			enum
			{
				SECTOR_CORRUPTED,
				INVALID_STATE = 0xB0
				// fids for invalid state, 0xB0 prefix and
				// state suffix -> 0xB0 - 0xB6
			};
		};

		void Initialize();
		void Uninitialize();
	}
}
