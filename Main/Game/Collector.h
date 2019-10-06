#pragma once

#include "../Device/FaultHandler.h"

#define GAME_MAX_PLAYERCOUNT 6

#pragma pack(push, 1)

namespace Game
{
	typedef unsigned char PlayerId;

	struct CollectData
	{
		unsigned char playerCount : 3;
		PlayerId playerIds[GAME_MAX_PLAYERCOUNT]
	};

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

		const CollectData* GetData();
	}
}

#pragma pack(pop)
