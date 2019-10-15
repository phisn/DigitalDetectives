#include "GameManager.h"
#include "../Game/PathManager.h"

namespace Extern
{
	extern Game::GameData* gameData;
}

namespace
{
	bool needsUpdate = false;
}

namespace Game
{
	namespace GameManager
	{
		Player* FindPlayer(const PlayerId id);
		bool ValidateTurn(
			const MapPosition source,
			const Turn turn);
		bool ValidateTurnBlack(
			const MapPosition source,
			const MapPosition target);
		bool RemovePlayerTicket(
			Player* const player, 
			const Ticket ticket);

		void Initialize()
		{
		}

		void Create()
		{
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

		bool MakeTurn(
			const PlayerId playerId, 
			const Turn turn)
		{
			Player* const player = FindPlayer(playerId);

			if (player == NULL)
			{
				return false;
			}

			if (!ValidateTurn(player->position, turn))
			{
				return false;
			}

			if (!RemovePlayerTicket(player, turn.ticket))
			{
				return false;
			}

			// set player position

			needsUpdate = true;

			return true;
		}

		bool MakeTurnDouble(
			const PlayerId player,
			const Turn firstTurn,
			const Turn secondTurn)
		{
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

		bool ValidateTurn(
			const MapPosition source,
			const Turn turn)
		{
			if (turn.ticket == Ticket::Black)
			{
				return ValidateTurnBlack(source, turn.position);
			}


		}

		bool ValidateTurnBlack(
			const MapPosition source,
			const MapPosition target)
		{
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

		const GameData* GetData()
		{
			return Extern::gameData;
		}
	}
}
