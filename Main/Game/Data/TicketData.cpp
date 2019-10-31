#include "TicketData.h"

namespace
{
	FlashString ticket_name_yellow = FPSTR("yellow");
	FlashString ticket_name_green = FPSTR("green");
	FlashString ticket_name_red = FPSTR("red");
	FlashString ticket_name_black = FPSTR("black");
	FlashString ticket_name_double = FPSTR("double");
}
/*
onvert between them
Yellow = Station::Taxi,
Green = Station::Bus,
Red = Station::Underground,
Black = Station::Ferry,
Double*/
namespace Game
{
	FlashString TicketToFlash(const Ticket ticket)
	{
		switch (ticket)
		{
		case Ticket::Yellow:
			return ticket_name_yellow;

		case Ticket::Green:
			return ticket_name_green;

		case Ticket::Red:
			return ticket_name_red;

		case Ticket::Black:
			return ticket_name_black;

		case Ticket::Double:
			return ticket_name_double;

		}
	}
}