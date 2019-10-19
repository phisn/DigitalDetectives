#pragma once

#include "../../Common/Common.h"

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

	} color;

	CRGB ColorToCRGB(const Color color);
}
