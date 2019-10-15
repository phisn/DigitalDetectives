#pragma once

#include "../../Game/Data/PlayerData.h"

namespace Game
{
	struct GameData
	{
		Player player[6];

		struct GameState
		{
			unsigned char round; // max 24
			// index in playersetup order
			unsigned char activePlayerIndex;
			PlayerId activePlayer;

		} state;
	};

	namespace GameManager
	{
		const GameData* GetData();
	}
}
