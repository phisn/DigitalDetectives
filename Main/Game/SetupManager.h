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
	}
}

#pragma pack(pop)
