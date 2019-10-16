#pragma once

#include "../Device/MemoryManager.h"

#include "../Game/BoardManager.h"
#include "../Game/Collector.h"
#include "../Game/Data/GameData.h"
#include "../Game/PathManager.h"
#include "../Game/SetupManager.h"

#pragma pack(push, 1)

namespace Game
{
	enum class Ticket
	{
		_Invalid = 255,

		// sync with station to easily
		// convert between them
		Yellow = Station::TAXI,
		Green = Station::BUS,
		Red = Station::UNDERGROUND,
		Black = Station::FERRY,
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

		struct TurnResult
		{
			bool success;
			FlashString message;
		};
		
		TurnResult MakeTurn(
			const PlayerId player,
			const Turn turn);
		TurnResult MakeTurnDouble(
			const PlayerId player,
			const Turn firstTurn,
			const Turn secondTurn);

		// avoid multiple calls!
		const Player* ReadPlayer(const PlayerId id);
		MapPosition GetLastVillianPosition();
	}
}

#pragma pack(pop)
