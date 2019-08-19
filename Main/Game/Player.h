#pragma once

#include <Common/Common.h>

RESOURCE_BEGIN

namespace Game
{
	struct Detective
	{
		int order; // ?
	};

	struct Villian
	{
		int blackTicketCount;
		int doubleTicketCount : 2;
	};
	
	struct Player
	{
		int position : 8;

		int yellowTickets;
		int greenTickets;
		int redTickets;

		// allow easy safe and load from
		// game-data perspective and also no need
		// for heavy dynamic allocation
		union
		{
			Detective detective;
			Villian villian;
		};
	};
}

RESOURCE_END
