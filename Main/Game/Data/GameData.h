#pragma once

#include "../../Game/Data/PlayerData.h"

namespace Game
{
	struct GameData
	{
		PlayerState player[6];

		struct GameState
		{
			unsigned char round; // max 24

			// index in playersetup order
			unsigned char activePlayerIndex;
			PlayerId activePlayer;
		} state;

		struct
		{
			Game::PlayerData::Type winner;

		} result;
	};

	namespace GameManager
	{
		const GameData* GetData();

		inline bool IsShowVillianPositionRound()
		{
			return GetData()->state.round % 5 == 3;
		}
	}
}
