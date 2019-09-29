#pragma once

#include "../Game/Settings.h"

#pragma pack(push, 1)

namespace Game
{
	struct SetupData
	{
		Settings settings;
	};

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
