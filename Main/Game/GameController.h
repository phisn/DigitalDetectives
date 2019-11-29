#pragma once

#include "../Communication/Interface.h"

#include "../Game/Data/GameSector.h"

#include "../Game/Collector.h"
#include "../Game/SetupManager.h"
#include "../Game/GameManager.h"
#include "../Game/FinishManager.h"

namespace Game
{
	namespace Controller
	{
		struct FID
		{
			enum
			{
				SECTOR_CORRUPTED = 2,
				INVALID_FINISH,
				INVALID_STATE = 0xB0,
				// fids for invalid state, 0xB0 prefix and
				// state suffix -> 0xB0 - 0xB6
			};
		};

		void Initialize();
		void Uninitialize();

		bool Process();

		void RequestFinish(); // think about finish (state)
		bool IsRestored();
	}
}
