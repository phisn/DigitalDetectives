#pragma once

#include "../Game/Player.h"
#include "../Game/Settings.h"

#pragma pack(push, 1)

namespace Game
{
	struct Data
	{
		Player player[6];
		Settings settings;
	};

	// Implementation in GameManager.cpp
	// GameManager has the only access to
	// change GameData
	const Data* GetData();
}

#pragma pack(pop)
