#pragma once

#include "../../Game/Data/CollectData.h"
#include "../../Game/Data/SetupData.h"
#include "../../Game/Data/GameData.h"

namespace Game
{
	enum class GameState : unsigned char
	{
		PreRunning = 255,

		Shutdown = 0, // zero for fresh start / clean
		Running,
		Setup,
		Collect,
	};

	struct GameSector
	{
		GameState state = GameState::PreRunning;

		GameData game;
		SetupData setup;
		CollectData collect;
	};

	namespace Controller
	{
		GameState GetState();
	}
}
