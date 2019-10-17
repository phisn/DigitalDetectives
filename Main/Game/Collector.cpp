#include "Collector.h"

namespace Extern
{
	extern Game::CollectData* collectData;
}

namespace
{
	bool isRestore = false;
	bool needsUpdate = true;

	// interface has the responsibility to ensure playercount
	FlashString fault_player_overflow = DEVICE_FAULT_MESSAGE("Player overflow caused by INTF");
}

namespace Game
{
	namespace Collector
	{
		void Create()
		{
			if (isRestore)
			{

			}
			else
			{
				Extern::collectData->playerCount = 0;
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
			isRestore = true;
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
			return nextPlayerId;
		}

		bool RemovePlayer(const PlayerId playerId)
		{
			for (int i = 0; i < Extern::collectData->playerCount; ++i)
				if (Extern::collectData->playerIds[i] == playerId)
				{
					for (int j = i; j < Extern::collectData->playerCount - 1; ++j)
					{
						Extern::collectData->playerIds[j] = Extern::collectData->playerIds[j + 1];
					}

					return true;
				}

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
