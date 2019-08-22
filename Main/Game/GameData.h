#pragma once

#include "../Game/Player.h"
#include "../Game/Settings.h"

#pragma pack(push, 1)

namespace Game
{
	// Implementation in GameManager.cpp
	// GameManager has the only acces to
	// change GameData
	struct Data
	{
		Player player[6];
		Settings settings;

	};
	
	const Data& GetData();
}

#pragma pack(pop)
