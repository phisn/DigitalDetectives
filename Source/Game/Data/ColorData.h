#pragma once

#include "../../Common/Common.h"
#include "../../Game/Data/TicketData.h"

namespace Game
{
	// player color is currently assigned
	// by index. first has to be black
	enum class Color : unsigned char
	{
		Black,

		Red,
		Green,
		Blue,

		Purple,
		Yellow,
	};

	FlashString ColorToFlash(const Color color);
	CRGB ColorToCRGB(const Color color);
	Game::Color TicketToColor(const Game::Ticket ticket);
}
