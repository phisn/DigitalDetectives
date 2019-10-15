#pragma once

#include "../../Game/Data/SettingsData.h"

namespace Game
{
	struct SetupData
	{
		Settings settings;
		// order (first player, next player | by id)
	};

	namespace SetupManager
	{
		const SetupData* GetData();
	}
}
