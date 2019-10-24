#include "ColorData.h"

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
