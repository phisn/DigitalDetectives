#pragma once

#include "../../Common/Common.h"
#include "../../Game/Data/TicketData.h"

#pragma pack(push, 1)

namespace Game
{
	struct Settings
	{
		CommonTickets beginCommonDetective;
		
		CommonTickets beginCommonVillian;
		VillianTickets beginSpecialVillian;
	};
}

#pragma pack(pop)
