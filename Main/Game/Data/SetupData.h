#pragma once

#include "../../Game/Data/CollectData.h"
#include "../../Game/Data/SettingsData.h"

namespace Game
{
	struct SetupData
	{
		Settings settings;

		struct PlayerContext
		{
			PlayerId villian;
			PlayerId order[COMMON_MAX_PLAYERCOUNT];

		} playerContext;
	};

	namespace SetupManager
	{
		const SetupData* GetData();
	}
}
