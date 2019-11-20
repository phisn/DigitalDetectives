#include "ColorData.h"

namespace
{
	FlashString color_black = FPSTR("Black");
	FlashString color_red = FPSTR("Red");
	FlashString color_green = FPSTR("Green");
	FlashString color_blue = FPSTR("Blue");
	FlashString color_purple = FPSTR("Purple");
	FlashString color_yellow = FPSTR("Yellow");
}

FlashString Game::ColorToFlash(const Game::Color color)
{
	switch (color)
	{
	case Color::Black:
		return color_black;

	case Color::Red:
		return color_red;

	case Color::Green:
		return color_green;

	case Color::Blue:
		return color_blue;

	case Color::Purple:
		return color_purple;

	case Color::Yellow:
		return color_yellow;

	}
}

CRGB Game::ColorToCRGB(const Color color)
{
	switch (color)
	{
	case Color::Black:
		return CRGB::Black;

	case Color::Red:
		return CRGB::Red;

	case Color::Green:
		return CRGB::Green;

	case Color::Blue:
		return CRGB::Blue;

	case Color::Purple:
		return CRGB::Purple;

	case Color::Yellow:
		return CRGB::Yellow;
	}
}
