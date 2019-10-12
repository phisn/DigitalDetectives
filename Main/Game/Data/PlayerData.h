#pragma once

#include "../Common/Common.h"
#include "../Game/CollectData.h"

#pragma pack(push, 1)

namespace Game
{
	struct Detective
	{
		enum class Color : unsigned char
		{
			Yellow,
			Red,
			Blue

		} color;

		unsigned char order : 3; // ?
	};

	struct Villian
	{
		unsigned char blackTicketCount : 3;
		unsigned char doubleTicketCount : 2;
	};

	struct Player
	{
		PlayerId player; // : 8

		MapPosition path[24]; // : 8
		MapPosition position; // : 8

		unsigned char yellowTickets : 6;
		unsigned char greenTickets : 6;
		unsigned char redTickets : 5;

		// allow easy safe and load from
		// game-data perspective and also no need
		// for heavy dynamic allocation
		union
		{
			Detective detective; // how to determine if player is evil?
			Villian villian;
		};
	};
}

#pragma pack(pop)
