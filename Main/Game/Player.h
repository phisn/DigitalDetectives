#pragma once

#include <Common/Common.h>

RESOURCE_BEGIN

namespace Game
{
	struct Detective
	{
		unsigned char order : 3; // ?
	};

	struct Villian
	{
		unsigned char blackTicketCount : 3;
		unsigned char doubleTicketCount : 2;
	};

	struct Player
	{
		unsigned char path[24]; // : 8
		unsigned char position; // : 8

		unsigned char yellowTickets : 6;
		unsigned char greenTickets : 6;
		unsigned char redTickets : 5;

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

int i = sizeof(Game::Player);

RESOURCE_END
