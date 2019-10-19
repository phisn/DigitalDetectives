#pragma once

#include "../../Common/Common.h"

#include "../../Game/Data/CollectData.h"
#include "../../Game/Data/ColorData.h"
#include "../../Game/Data/TicketData.h"

#pragma pack(push, 1)

namespace Game
{
	struct Detective
	{
	};

	struct Villian
	{
		VillianTickets ticket;
	};

	// does changes while playing
	// created in gamem
	struct PlayerState
	{
		MapPosition path[24]; // : 8
		MapPosition position; // : 8

		CommonTickets ticket;

		// allow easy safe and load from
		// game-data perspective and also no need
		// for heavy dynamic allocation
		union
		{
			Detective detective;
			Villian villian;
		};
	};

	// doesnt change while playing
	// created in setupm
	struct PlayerData
	{
		PlayerId player;

		enum class Type : unsigned char
		{
			Villian,
			Detective
		} type : 1;

		Color color;
	};

	// player container for READ outside from
	// gamemanager and setupmanager
	struct Player
	{
		const PlayerState* state;
		const PlayerData* data;
	};

	constexpr Color VillianColor = Color::Black;
}

#pragma pack(pop)
