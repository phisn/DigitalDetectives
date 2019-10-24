#pragma once

#include "../../Game/PathManager.h"

#pragma pack(push, 1)

namespace Game
{
	enum class Ticket : unsigned char
	{
		_Invalid = 255,

		// sync with station to easily
		// convert between them
		Yellow = Station::Taxi,
		Green = Station::Bus,
		Red = Station::Underground,
		Black = Station::Ferry,
		Double
	};

	// max 255 for all tickets
	struct CommonTickets
	{
		unsigned char yellowTicketCount;
		unsigned char greenTicketCount;
		unsigned char redTicketCount;
	};

	struct VillianTickets
	{
		unsigned char blackTicketCount;
		unsigned char doubleTicketCount;
	};

	namespace DefaultTickets
	{
		constexpr CommonTickets beginCommonDetective = { 10, 8, 4 };

		constexpr CommonTickets beginCommonVillian = { 4, 3, 3 };
		constexpr VillianTickets beginSpecialVillian = { 2, 0 };
	}
}

#pragma pack(pop)
