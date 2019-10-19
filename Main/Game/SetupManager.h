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

		void AdjustCommonDetectiveTickets(const CommonTickets);
		void AdjustCommonVillianTickets(const CommonTickets);
		void AdjustSpecialVillianTickets(const VillianTickets);

		bool Finish();
	}
}

#pragma pack(pop)
