#pragma once

#include "Common.h"

namespace Game
{
	RESOURCE_BEGIN

	struct Player
	{
		byte position[24];

		byte yellowTickets;
		byte greenTickets;
		byte redTickets;
	};

	struct Enemy
		:
		public Player
	{
		byte lastShownPositions[5];

		byte blackTickets;
		byte doubleTickets;
	};

	struct Detective
		:
		public Player
	{
		byte color;
	};

	RESOURCE_END
}

#pragma pack(pop)
