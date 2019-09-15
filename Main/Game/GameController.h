#pragma once

#include "../Game/Collector.h"
#include "../Game/GameManager.h"
#include "../Game/SetupManager.h"

namespace Game
{
	enum class State : unsigned char
	{
		Running = 0b0011'0000,

		Setup,
		Collect,
		Restore,

		Finished,
		Paused,
		Shutdown
	};

	struct Sector
	{
		unsigned char check;

		struct Data
		{
			GameData game;
			SetupData setup;
			CollectData collect;

			State state;
		} data;
	};

	namespace Controller
	{
		struct FID
		{
			enum
			{
				SECTOR_CORRUPTED,
				INVALID_STATE = 0b1000'0000
				// fids for invalid state, 0xB0 prefix and
				// state suffix -> 0xB0 - 0xB6
			};
		};

		void Initialize();
		void Uninitialize();
	}
}
