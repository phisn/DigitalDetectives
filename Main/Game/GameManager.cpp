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
	Game::Player dynamicPlayer[COMMON_MAX_PLAYERCOUNT];
}

namespace Game
{
	namespace GameManager
	{
		// can fail (-1)
		int FindPlayerIndex(const PlayerId id);
		int FindVillianIndex();

		bool ValidateTurn(
			const MapPosition source,
			const Turn turn);
		bool ValidateTurnBlack(
			const MapPosition source,
			const MapPosition target);
		bool RemovePlayerTicket(
			const PlayerData::Type type,
			PlayerState* const player, 
			const Ticket ticket);
		bool AddPlayerTicket(
			const PlayerData::Type type,
			PlayerState* const player,
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

			PathManager::FindRandomStartsResult randomStarts = PathManager::FindRandomStarts();

			for (int i = 0; i < Collector::GetData()->playerCount; ++i)
			{
				PlayerState* const player = &Extern::gameData->player[i];

				// init ticketcount
				if (SetupManager::GetData()->playerContext.data[i].type == PlayerData::Type::Villian)
				{
					player->ticket = SetupManager::GetData()->settings.beginCommonVillian;
					player->villian.ticket = SetupManager::GetData()->settings.beginSpecialVillian;
				}
				else
				{
					player->ticket = SetupManager::GetData()->settings.beginCommonDetective;
				}

				// intit startposition
				player->position = randomStarts.starts[i];

				dynamicPlayer[i].state = player;
				dynamicPlayer[i].data = &SetupManager::GetData()->playerContext.data[i];
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

			const int playerIndex = FindPlayerIndex(playerId);

			if (playerIndex == -1)
			{
				return { false, turn_fail_playernotfound };
			}

			PlayerState* const playerState = &Extern::gameData->player[playerIndex];
			const PlayerData* const playerData = &SetupManager::GetData()->playerContext.data[playerIndex];
			
			if (playerData->type == PlayerData::Type::Detective &&
				   (turn.ticket == Ticket::Black ||
					turn.ticket == Ticket::Double))
			{
				return { false, turn_fail_ticketnotavaible };
			}

			if (!ValidateTurn(playerState->position, turn))
			{
				return { false, turn_fail_invalidturn };
			}

			// also checks if playe has ticket
			if (!RemovePlayerTicket(
					playerData->type, 
					playerState, 
					turn.ticket))
			{
				return { false, turn_fail_ticketnotfound };
			}

			playerState->path[Extern::gameData->state.round] = playerState->position;
			playerState->position = turn.position;

			if (playerData->type == PlayerData::Type::Detective)
			{
				PlayerState* const villian = &Extern::gameData->player[FindVillianIndex()];

				if (villian->position == playerState->position)
				{
					// ...
				}

				AddPlayerTicket(
					PlayerData::Type::Villian, 
					villian, 
					turn.ticket);
			}
			else
			{
				if (Extern::gameData->state.round == 24)
				{
					// game over for detectives
				}

				if (IsShowVillianPositionRound())
				{
					lastVillianPosition = playerState->position;
				}
			}

			// check for finished round
			if (++Extern::gameData->state.activePlayerIndex >= Collector::GetData()->playerCount)
			{
				++Extern::gameData->state.round;
				Extern::gameData->state.activePlayerIndex = 0;
				
				// ...
			}
			
			// select next playerId as active player
			Extern::gameData->state.activePlayer = SetupManager::GetData()
				->playerContext.data[Extern::gameData->state.activePlayerIndex].player;

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

		int FindPlayerIndex(const PlayerId id)
		{
			for (int i = 0; i < Collector::GetData()->playerCount; ++i)
				if (SetupManager::GetData()->playerContext.data[i].player == id)
				{
					return i;
				}

			return -1;
		}

		int FindVillianIndex()
		{
			for (int i = 0; i < Collector::GetData()->playerCount; ++i)
				if (SetupManager::GetData()->playerContext.data[i].type == PlayerData::Type::Villian)
				{
					return i;
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
			case Station::Underground:
				for (int i = 0; result.undergroundStations[i]; ++i)
					if (result.undergroundStations[i] == target)
					{
						return true;
					}


			case Station::Bus:
				for (int i = 0; result.busStations[i]; ++i)
					if (result.busStations[i] == target)
					{
						return true;
					}

			case Station::Taxi:
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
			const PlayerData::Type type,
			PlayerState* const player,
			const Ticket ticket)
		{
			// optimizing not possible, bitfields are used
			switch (ticket)
			{
			case Ticket::Yellow:
				if (player->ticket.yellowTicketCount > 0)
				{
					--player->ticket.yellowTicketCount;
					return true;
				}

				break;
			case Ticket::Green:
				if (player->ticket.greenTicketCount > 0)
				{
					--player->ticket.greenTicketCount;
					return true;
				}

				break;
			case Ticket::Red:
				if (player->ticket.redTicketCount > 0)
				{
					--player->ticket.redTicketCount;
					return true;
				}

				break;
			case Ticket::Black:
				if (type == PlayerData::Type::Detective)
				{
					break;
				}

				if (player->villian.ticket.blackTicketCount > 0)
				{
					--player->villian.ticket.blackTicketCount;
					return true;
				}

				break;
			case Ticket::Double:
				if (type == PlayerData::Type::Detective)
				{
					break;
				}

				if (player->villian.ticket.doubleTicketCount > 0)
				{
					--player->villian.ticket.doubleTicketCount;
					return true;
				}

				break;
			}

			return false;
		}

		bool AddPlayerTicket(
			const PlayerData::Type type,
			PlayerState* const player,
			const Ticket ticket)
		{
			// optimizing not possible, bitfields are used
			switch (ticket)
			{
			case Ticket::Yellow:
				++player->ticket.yellowTicketCount;

				break;
			case Ticket::Green:
				++player->ticket.greenTicketCount;

				break;
			case Ticket::Red:
				++player->ticket.redTicketCount;

				break;
			case Ticket::Black:
				if (type == PlayerData::Type::Detective)
				{
					return false;
				}

				++player->villian.ticket.blackTicketCount;

				break;
			case Ticket::Double:
				if (type == PlayerData::Type::Detective)
				{
					return false;
				}

				++player->villian.ticket.doubleTicketCount;

				break;
			}

			return true;
		}

		const Player* ReadPlayer(const PlayerId id)
		{
			const int index = FindPlayerIndex(id);

			if (index == -1)
			{
				return NULL;
			}

			return &dynamicPlayer[index];
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
