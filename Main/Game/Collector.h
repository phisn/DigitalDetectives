#pragma once

#include "../Device/FaultHandler.h"

#include "../Game/Data/CollectData.h"

#pragma pack(push, 1)

namespace Game
{
	namespace Collector
	{
		struct FID
		{
			enum
			{
				// interface has the responsibility to ensure playercount
				PLAYER_OVERFLOW = 2
			};
		};

		void Create();
		bool Process();
		void Restore();

		PlayerId CreatePlayer();

		bool RemovePlayer(const PlayerId playerId);
		bool ExistsPlayer(const PlayerId playerId);
		
		bool Finish();
	}
}

#pragma pack(pop)
