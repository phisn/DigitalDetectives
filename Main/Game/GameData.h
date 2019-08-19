#pragma once

#include <Game/Player.h>
#include <Game/Settings.h>

RESOURCE_BEGIN

namespace Game
{
	struct Data
	{
		Player player;
		Settings settings;
	};
}

RESOURCE_END
