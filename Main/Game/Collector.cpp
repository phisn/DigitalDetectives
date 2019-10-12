#include "Collector.h"

namespace Extern
{
	extern Game::CollectData* collectData;
}

namespace
{
	bool isRestore = false;
	bool needsUpdate = false;

	// interface has the responsibility to ensure playercount
	FlashString fault_player_overflow = DEVICE_FAULT_MESSAGE("Player overflow caused by INTF");
}

namespace Game
{
	namespace Collector
	{
		void Create()
		{
			if (!isRestore)
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
			if (Extern::collectData->playerCount >= COMMON_MAX_PLAYERCOUNT)
			{
				Device::FaultHandler::Handle(
				{
					Device::FaultModule::NetworkManager,
					(Device::FailureId) FID::PLAYER_OVERFLOW,
					fault_player_overflow
				}, true);
			}

			const PlayerId nextPlayerId = (PlayerId)rand();
			Extern::collectData->playerIds[Extern::collectData->playerCount] = nextPlayerId;
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
	}
}
