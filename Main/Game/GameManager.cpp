#include "GameManager.h"

namespace Extern
{
	extern Game::GameData* gameData;
}

namespace
{
	bool needsUpdate = true;

	FlashString turn_fail_activeplayer = FPSTR("PlayerId not active");
	FlashString turn_fail_playernotfound = FPSTR("PlayerId not found");
	FlashString turn_fail_invalidturn = FPSTR("Got invalid turn");
	FlashString turn_fail_ticketnotfound = FPSTR("Ticket not found");
	FlashString turn_fail_ticketnotavaible = FPSTR("Villian ticket not avaiable");

	Game::MapPosition lastVillianPosition;
}

namespace Game
{
	namespace GameManager
	{
		// can return null
		Player* FindPlayer(const PlayerId id);
		Player* FindVillian();

		bool ValidateTurn(
			const MapPosition source,
			const Turn turn);
		bool ValidateTurnBlack(
			const MapPosition source,
			const MapPosition target);
		bool RemovePlayerTicket(
			Player* const player, 
			const Ticket ticket);
		bool AddPlayerTicket(
			Player* const player,
			const Ticket ticket);

		void Initialize()
		{
		}

		void Create()
		{
			DEBUG_MESSAGE("GameManager create");

			Extern::gameData->state.round = 0;
			Extern::gameData->state.activePlayer = SetupManager::GetData()->playerContext.villian;
			Extern::gameData->state.activePlayerIndex = 0;

			for (int i = 0; i < Collector::GetData()->playerCount; ++i)
			{
				Player* const player = &Extern::gameData->player[i];
				player->player = Collector::GetData()->playerIds[i];
				
				if (player->player == SetupManager::GetData()->playerContext.villian)
				{
					player->type = Player::Type::Villian;

					player->yellowTickets = SetupManager::GetData()->settings.beginVillianYellowCount;
					player->greenTickets = SetupManager::GetData()->settings.beginVillianGreenCount;
					player->redTickets = SetupManager::GetData()->settings.beginVillianRedCount;

					player->villian.blackTicketCount = SetupManager::GetData()->settings.beginVillianBlackCount;
					player->villian.doubleTicketCount = SetupManager::GetData()->settings.beginVillianDoubleCount;
				}
				else
				{
					player->type = Player::Type::Detective;

					player->yellowTickets = SetupManager::GetData()->settings.beginDetectiveYellowCount;
					player->greenTickets = SetupManager::GetData()->settings.beginDetectiveGreenCount;
					player->redTickets = SetupManager::GetData()->settings.beginDetectiveRedCount;

					player->detective.color;
				}

				player->position = random(200); // TODO: get defaults
			}
		}

		bool Process()
		{
			if (needsUpdate)
			{
				needsUpdate = false;
				return true;
			}

			return false;
		}

		void Restore()
		{
		}

		TurnResult MakeTurn(
			const PlayerId playerId, 
			const Turn turn)
		{
			if (playerId != Extern::gameData->state.activePlayer)
			{
				return { false, turn_fail_activeplayer };
			}

			Player* const player = FindPlayer(playerId);

			if (player == NULL)
			{
				return { false, turn_fail_playernotfound };
			}

			int b = (int) player->type;
			DEBUG_MESSAGE("Make turn as: ");
			DEBUG_MESSAGE(b);

			if (player->type == Player::Type::Detective &&
				   (turn.ticket == Ticket::Black ||
					turn.ticket == Ticket::Double))
			{
				return { false, turn_fail_ticketnotavaible };
			}

			if (!ValidateTurn(player->position, turn))
			{
				return { false, turn_fail_invalidturn };
			}

			// also checks if playe has ticket
			if (!RemovePlayerTicket(player, turn.ticket))
			{
				return { false, turn_fail_ticketnotfound };
			}

			player->path[Extern::gameData->state.round] = player->position;
			player->position = turn.position;

			if (player->type == Player::Type::Detective)
			{
				Player* const villian = FindVillian();

				if (villian->position == player->position)
				{
					// ...
				}

				AddPlayerTicket(villian, turn.ticket);
			}
			else
			{
				if (Extern::gameData->state.round == 24)
				{
					// game over
				}

				if (Extern::gameData->state.round % 5 == 3)
				{
					lastVillianPosition = player->position;
				}
			}

			// select next player index as active player and check for finished round
			if (++Extern::gameData->state.activePlayerIndex >= Collector::GetData()->playerCount)
			{
				Extern::gameData->state.activePlayerIndex = 0;
				++Extern::gameData->state.round;
				
				// ...
			}
			
			// select next playerId as active player
			Extern::gameData->state.activePlayer = SetupManager::GetData()
				->playerContext.order[Extern::gameData->state.activePlayerIndex];

			needsUpdate = true;
			return { true, NULL };
		}

		TurnResult MakeTurnDouble(
			const PlayerId player,
			const Turn firstTurn,
			const Turn secondTurn)
		{
			return { };
		}

		Player* FindPlayer(const PlayerId id)
		{
			for (int i = 0; i < Collector::GetData()->playerCount; ++i)
				if (Extern::gameData->player[i].player == id)
				{
					return &Extern::gameData->player[i];
				}

			return NULL;
		}

		Player* FindVillian()
		{
			for (int i = 0; i < Collector::GetData()->playerCount; ++i)
				if (Extern::gameData->player[i].type == Player::Type::Villian)
				{
					return &Extern::gameData->player[i];
				}
			// unreachable
		}

		bool ValidateTurn(
			const MapPosition source,
			const Turn turn)
		{
			if (turn.ticket == Ticket::Black)
			{
				return ValidateTurnBlack(source, turn.position);
			}

			PathManager::FindOptionsSpecificResult result = PathManager::FindOptionsSpecific(
				source,
				(Station::Type) turn.ticket);

			for (int i = 0; i < result.stationCount; ++i)
				if (result.station[i] == turn.position)
				{
					return true;
				}

			return false;
		}

		bool ValidateTurnBlack(
			const MapPosition source,
			const MapPosition target)
		{
			Station sourceStation = PathManager::GetStationType(source);
			PathManager::FindOptionsResult result = PathManager::FindOptions(source);

			switch (sourceStation.type)
			{ // fall though all
			case Station::UNDERGROUND:
				for (int i = 0; result.undergroundStations[i]; ++i)
					if (result.undergroundStations[i] == target)
					{
						return true;
					}


			case Station::BUS:
				for (int i = 0; result.busStations[i]; ++i)
					if (result.busStations[i] == target)
					{
						return true;
					}

			case Station::TAXI:
				for (int i = 0; result.taxiStations[i]; ++i)
					if (result.taxiStations[i] == target)
					{
						return true;
					}

				if (sourceStation.isFerry && ( // optimized forloop
						result.ferryStations[0] == target ||
						result.ferryStations[1] == target))
				{
					return true;
				}

				break;
			}

			return false;
		}

		bool RemovePlayerTicket(
			Player* const player,
			const Ticket ticket)
		{
			// optimizing not possible, bitfields are used
			switch (ticket)
			{
			case Ticket::Yellow:
				if (player->yellowTickets > 0)
				{
					--player->yellowTickets;
					return true;
				}

				break;
			case Ticket::Green:
				if (player->greenTickets > 0)
				{
					--player->greenTickets;
					return true;
				}

				break;
			case Ticket::Red:
				if (player->redTickets > 0)
				{
					--player->redTickets;
					return true;
				}

				break;
			case Ticket::Black:
				if (player->type == Player::Type::Detective)
				{
					break;
				}

				if (player->villian.blackTicketCount > 0)
				{
					--player->villian.blackTicketCount;
					return true;
				}

				break;
			case Ticket::Double:
				if (player->type == Player::Type::Detective)
				{
					break;
				}

				if (player->villian.doubleTicketCount > 0)
				{
					--player->villian.doubleTicketCount;
					return true;
				}

				break;
			}

			return false;
		}

		bool AddPlayerTicket(
			Player* const player,
			const Ticket ticket)
		{
			// optimizing not possible, bitfields are used
			switch (ticket)
			{
			case Ticket::Yellow:
				++player->yellowTickets;

				break;
			case Ticket::Green:
				++player->greenTickets;

				break;
			case Ticket::Red:
				++player->redTickets;

				break;
			case Ticket::Black:
				if (player->type == Player::Type::Detective)
				{
					return false;
				}

				++player->villian.blackTicketCount;

				break;
			case Ticket::Double:
				if (player->type == Player::Type::Detective)
				{
					return false;
				}

				++player->villian.doubleTicketCount;

				break;
			}

			return true;
		}

		const Player* ReadPlayer(const PlayerId id)
		{
			return FindPlayer(id);
		}

		MapPosition GetLastVillianPosition()
		{
			return lastVillianPosition;
		}

		const GameData* GetData()
		{
			return Extern::gameData;
		}
	}
}
