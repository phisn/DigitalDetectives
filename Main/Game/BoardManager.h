#pragma once

#include "../Device/OutputManager.h"
#include "../Device/MapManager.h"

#include "../Game/Data/GameSector.h"

namespace Game
{
	namespace BoardManager
	{
		void Process();
		void Update();

		void OnStateChanged(const Game::GameState newState);
		void ReloadLcd();
	}
}
