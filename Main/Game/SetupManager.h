#pragma once

#include "../Game/Data/SetupData.h"

#pragma pack(push, 1)

namespace Game
{
	namespace SetupManager
	{
		struct FID
		{
			enum
			{
			};
		};

		void Create();
		bool Process();
		void Restore();

		void AdjustDetectiveYellowTickets(const int count);
		void AdjustDetectiveGreenTickets(const int count);
		void AdjustDetectiveRedTickets(const int count);

		void AdjustVillianYellowTickets(const int count);
		void AdjustVillianGreenTickets(const int count);
		void AdjustVillianRedTickets(const int count);
		void AdjustVillianBlackTickets(const int count);
		void AdjustVillianDoubleTickets(const int count);

		bool Finish();
	}
}

#pragma pack(pop)
