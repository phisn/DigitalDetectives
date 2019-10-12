#pragma once

#include "../Game/Data/PlayerData.h"

namespace Game
{
	struct GameData
	{
		Player player[6];

		struct GameState
		{
			PlayerId currentPlayer;

		} state;
	};

	namespace GameManager
	{
		const GameData* GetData();
	}
}
