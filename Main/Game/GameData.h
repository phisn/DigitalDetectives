#pragma once

#include <Game/Player.h>
#include <Game/Settings.h>

RESOURCE_BEGIN

namespace Game
{
	// Implementation in GameManager.cpp
	// GameManager has the only acces to
	// change GameData
	const struct Data
	{
		Player player[6];
		Settings settings;

	}& GetData();
}

RESOURCE_END
