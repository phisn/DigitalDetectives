#pragma once

#include "../../Game/Data/CollectData.h"
#include "../../Game/Data/SetupData.h"
#include "../../Game/Data/GameData.h"

namespace Game
{
	enum class GameState : unsigned char
	{
		Shutdown = 0, // zero for fresh start / clean
		Running,
		Setup,
		Collect
	};

	struct GameSector
	{
		GameData game;
		SetupData setup;
		CollectData collect;

		GameState state;
	};

	namespace Controller
	{
		GameState GetState();
	}
}
