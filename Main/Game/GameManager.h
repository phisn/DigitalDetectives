#pragma once

#include "../Device/MemoryManager.h"

#include "../Game/BoardManager.h"
#include "../Game/Data/GameData.h"

#pragma pack(push, 1)

namespace Game
{
	enum class Ticket
	{
		_Invalid,

		Yellow,
		Green,
		Red,
		Black,
		Double
	};

	struct Turn
	{
		Ticket ticket;
		MapPosition position;
	};

	namespace GameManager
	{
		struct FID
		{
			enum
			{
				SECTOR_CORRUPTED = 2
			};
		};

		void Create();
		bool Process();
		void Restore();

		bool MakeTurn(
			const PlayerId player,
			const Turn turn);
		bool MakeTurnDouble(
			const PlayerId player,
			const Turn firstTurn,
			const Turn secondTurn);
	}
}

#pragma pack(pop)
