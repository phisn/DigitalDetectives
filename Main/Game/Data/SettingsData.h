#pragma once

#include "../../Common/Common.h"

#pragma pack(push, 1)

namespace Game
{
	namespace Default
	{
		constexpr int beginDetectiveYellowCount = 10;
		constexpr int beginDetectiveGreenCount = 8;
		constexpr int beginDetectiveRedCount = 4;

		constexpr int beginVillianYellowCount = 4;
		constexpr int beginVillianGreenCount = 3;
		constexpr int beginVillianRedCount = 3;
		constexpr int beginVillianDoubleCount = 2;
	}

	struct Settings
	{
		int beginDetectiveYellowCount;
		int beginDetectiveGreenCount;
		int beginDetectiveRedCount;

		int beginVillianYellowCount;
		int beginVillianGreenCount;
		int beginVillianRedCount;
		int beginVillianBlackCount;
		int beginVillianDoubleCount;
	};
}

#pragma pack(pop)
