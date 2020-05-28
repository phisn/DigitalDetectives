#include "Collector.h"

namespace Extern
{
	extern Game::CollectData* collectData;
}

namespace
{
	bool needsUpdate = true;

	// interface has the responsibility to ensure playercount
	FlashString fault_player_overflow = DEVICE_FAULT_MESSAGE("Player overflow caused by Interfc");
}

namespace Game
{
	namespace Collector
	{
		void Create()
		{
			Extern::collectData->playerCount = 0;
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

		bool Restore()
		{
			// TODO: Implement check
			return true;
		}

		PlayerId CreatePlayer()
		{
			DEBUG_MESSAGE("Creating new player");

			if (Extern::collectData->playerCount >= COMMON_MAX_PLAYERCOUNT)
			{
				Device::FaultHandler::Handle(
				{
					Device::FaultModule::Collector,
					(Device::FailureId) FID::PLAYER_OVERFLOW,
					fault_player_overflow
				}, true);
			}

			needsUpdate = true;

			const PlayerId nextPlayerId = (PlayerId) rand();
			Extern::collectData->playerIds[Extern::collectData->playerCount++] = nextPlayerId;


			DEBUG_MESSAGE("GOT GM INF");
			for (int i = 0; i < Game::Collector::GetData()->playerCount; ++i)
				DEBUG_MESSAGE(Extern::collectData->playerIds[i]);

			DEBUG_MESSAGE("HAVE GM INF");
			return nextPlayerId;
		}

		bool RemovePlayer(const PlayerId playerId)
		{
			DEBUG_MESSAGE("PCOUNT");
			DEBUG_MESSAGE(Extern::collectData->playerCount);

			DEBUG_MESSAGE("GOT GM PRE");

			for (int i = 0; i < Game::Collector::GetData()->playerCount; ++i)
				DEBUG_MESSAGE(Extern::collectData->playerIds[i]);

			DEBUG_MESSAGE("HAVE GM PRE");

			for (int i = 0; i < Extern::collectData->playerCount; ++i)
				if (Extern::collectData->playerIds[i] == playerId)
				{
					DEBUG_MESSAGE("FOUND");

					for (int j = i; j < Extern::collectData->playerCount - 1; ++j)
					{
						Extern::collectData->playerIds[j] = Extern::collectData->playerIds[j + 1];
					}

					--Extern::collectData->playerCount;

					needsUpdate = true;
					return true;
				}

			DEBUG_MESSAGE("REMOVE_PLAYER_COLLECT_FORBID");

#ifdef VM_DEBUG
			DEBUG_MESSAGE("GOT GM");
			DEBUG_MESSAGE(playerId);
			DEBUG_MESSAGE("HAVE GM");

			for (int i = 0; i < Game::Collector::GetData()->playerCount; ++i)
				DEBUG_MESSAGE(Extern::collectData->playerIds[i]);

			DEBUG_MESSAGE("END HAVE GM");
#endif

			return false;
		}

		bool ExistsPlayer(const PlayerId playerId)
		{
			for (int i = 0; i < Extern::collectData->playerCount; ++i)
				if (Extern::collectData->playerIds[i] == playerId)
				{
					return true;
				}

			return false;
		}

		int FindPlayerIndex(const PlayerId playerId)
		{
			DEBUG_MESSAGE("FIND_PINDEX");
			for (int i = 0; i < Extern::collectData->playerCount; ++i)
				if (Extern::collectData->playerIds[i] == playerId)
				{
					DEBUG_MESSAGE("PINDEX");
					DEBUG_MESSAGE(i);

					return i;
				}

			DEBUG_MESSAGE("NO PINDEX");

			return -1;
		}

		const CollectData* GetData()
		{
			return Extern::collectData;
		}

		bool Finish()
		{
			const bool result = Extern::collectData->playerCount >= 4;

			if (result)
			{
				DEBUG_MESSAGE("Player count is over 4: ");
			}
			else
			{
				DEBUG_MESSAGE("Player count is not over 4: ");
			}

			DEBUG_MESSAGE(Extern::collectData->playerCount);

			return result;
		}
	}
}
