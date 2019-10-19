#include "SetupManager.h"

// TODO remove (debug)
#include "../Game/GameController.h"

namespace Extern
{
	extern Game::SetupData* setupData;
}

namespace
{
	bool needsUpdate = true;
}

namespace Game
{
	namespace SetupManager
	{
		void CreateTicketCount();
		void CreatePlayerContext();

		void Create()
		{
			DEBUG_MESSAGE("SetupManager Create");

			CreateTicketCount();

			// playercontext is first created
			// at request finish, to take player
			// perferences into account

			// CreatePlayerContext();
		}

		void CreateTicketCount()
		{
			Extern::setupData->settings.beginCommonDetective = DefaultTickets::beginCommonDetective;
			Extern::setupData->settings.beginCommonVillian = DefaultTickets::beginCommonVillian;
			Extern::setupData->settings.beginSpecialVillian = DefaultTickets::beginSpecialVillian;

			// for every detective
			Extern::setupData->settings.beginSpecialVillian.blackTicketCount = Collector::GetData()->playerCount - 1;
		}

		void CreatePlayerContext()
		{
			// shuffle players for random order
			PlayerId playerOrder[COMMON_MAX_PLAYERCOUNT];

			memcpy(playerOrder,
				Collector::GetData()->playerIds,
				Collector::GetData()->playerCount * sizeof(PlayerId)
			);

			for (int i = 0; i < Collector::GetData()->playerCount; ++i)
			{
				int randomIndex = random(Collector::GetData()->playerCount);

				// swap
				PlayerId temp = playerOrder[randomIndex];
				playerOrder[randomIndex] = playerOrder[i];
				playerOrder[i] = temp;
			}

			// create playerData
			for (int i = 0; i < Collector::GetData()->playerCount; ++i)
			{
				Extern::setupData->playerContext.data[i].player = playerOrder[i];
				Extern::setupData->playerContext.data[i].type = i == 0
					? PlayerData::Type::Villian
					: PlayerData::Type::Detective;

				// change later by preference
				Extern::setupData->playerContext.data[i].color = (Color) i;
			}

			// first is villian
			Extern::setupData->playerContext.villian = playerOrder[0];
		}

		bool Process()
		{
			// TODO: change late, currently in debug
			DEBUG_MESSAGE("Setup auto request finish");
			Game::Controller::RequestFinish();

			return false;
		}

		void Restore()
		{
		}

		void AdjustCommonDetectiveTickets(const CommonTickets ticketCount)
		{
			Extern::setupData->settings.beginCommonDetective = ticketCount;
			needsUpdate = true;
		}

		void AdjustCommonVillianTickets(const CommonTickets ticketCount)
		{
			Extern::setupData->settings.beginCommonVillian = ticketCount;
			needsUpdate = true;
		}

		void AdjustSpecialVillianTickets(const VillianTickets ticketCount)
		{
			Extern::setupData->settings.beginSpecialVillian = ticketCount;
			needsUpdate = true;
		}

		const Game::SetupData* GetData()
		{
			return Extern::setupData;
		}

		bool Finish()
		{
			CreatePlayerContext();

			return true;
		}
	}
}
