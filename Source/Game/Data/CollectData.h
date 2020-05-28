#pragma once

#include "../../Common/Common.h"

namespace Game
{
	typedef unsigned char PlayerId;

	struct CollectData
	{
		unsigned char playerCount;
		PlayerId playerIds[COMMON_MAX_PLAYERCOUNT];
	};

	namespace Collector
	{
		const CollectData* GetData();
	}
}
