#include "SetupManager.h"

namespace Extern
{
	extern Game::SetupData* setupData;
}

namespace Game
{
	namespace SetupManager
	{
		void Create()
		{
			Extern::setupData->settings.beginDetectiveYellowCount = Default::beginDetectiveYellowCount;
			Extern::setupData->settings.beginDetectiveGreenCount = Default::beginDetectiveGreenCount;
			Extern::setupData->settings.beginDetectiveRedCount = Default::beginDetectiveRedCount;
			
			Extern::setupData->settings.beginVillianYellowCount = Default::beginVillianYellowCount;
			Extern::setupData->settings.beginVillianGreenCount = Default::beginVillianGreenCount;
			Extern::setupData->settings.beginVillianRedCount = Default::beginVillianRedCount;
			Extern::setupData->settings.beginVillianBlackCount = Collector::GetData()->playerCount - 1; // for every detective
			Extern::setupData->settings.beginVillianDoubleCount = Default::beginVillianDoubleCount;

			// copy and shuffel for random order
			memcpy(
				Extern::setupData->playerContext.order, 
				Collector::GetData()->playerIds, 
				sizeof(PlayerId) * Collector::GetData()->playerCount);

			for (int i = 0; i < Collector::GetData()->playerCount; ++i)
			{
				int randomIndex = rand() % Collector::GetData()->playerCount;

				// swap
				PlayerId temp = Extern::setupData->playerContext.order[randomIndex];
				Extern::setupData->playerContext.order[randomIndex] = Extern::setupData->playerContext.order[i];
				Extern::setupData->playerContext.order[i] = temp;
			}

			// first is villian
			Extern::setupData->playerContext.villian = Extern::setupData->playerContext.order[0];
		}

		bool Process()
		{
			return false;
		}

		void Restore()
		{
		}

		void AdjustDetectiveYellowTickets(const int count)
		{
			Extern::setupData->settings.beginDetectiveYellowCount = count;
		}

		void AdjustDetectiveGreenTickets(const int count)
		{
			Extern::setupData->settings.beginDetectiveGreenCount = count;
		}

		void AdjustDetectiveRedTickets(const int count)
		{
			Extern::setupData->settings.beginDetectiveRedCount = count;
		}

		void AdjustVillianYellowTickets(const int count)
		{
			Extern::setupData->settings.beginVillianYellowCount = count;
		}

		void AdjustVillianGreenTickets(const int count)
		{
			Extern::setupData->settings.beginVillianGreenCount = count;
		}

		void AdjustVillianRedTickets(const int count)
		{
			Extern::setupData->settings.beginVillianRedCount = count;
		}

		void AdjustVillianBlackTickets(int count)
		{
			Extern::setupData->settings.beginVillianBlackCount = count;
		}

		void AdjustVillianDoubleTickets(int count)
		{
			Extern::setupData->settings.beginVillianDoubleCount = count;
		}

		const Game::SetupData* GetData()
		{
			return Extern::setupData;
		}
	}
}
