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
		void Begin(SetupData* const data);
		bool Restore(SetupData* const data);
	}
}

#pragma pack(pop)
