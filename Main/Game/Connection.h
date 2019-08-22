#pragma once

#include <Common/Common.h>

RESOURCE_BEGIN

namespace Game
{
	struct Station
	{
		enum Type : unsigned char
		{
			TAXI,
			BUS,
			UNDERGROUND,
			FERRY

		} type : 3;

		unsigned char isFerry : 1;
	};

	struct Connection // 472
	{
		unsigned char station1 : 8; 
		unsigned char station2 : 8;

		Station::Type type : 3;
	};

	namespace Path
	{
		struct FindOptionsResult
		{
			unsigned char station[14];
			unsigned char stationCount;

		} FindOptions(
			const int stationId,
			const Station::Type type);
	}
};

RESOURCE_END
