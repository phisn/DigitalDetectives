#pragma once

#include <Common/Common.h>

RESOURCE_BEGIN

namespace Game
{
	struct Station
	{
		enum Type : unsigned char
		{
			TAXI = 0,
			BUS = 1,
			UNDERGROUND = 2,
			FERRY = 3

		} type : 2;

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
		struct FindOptionsSpecificResult
		{
			unsigned char station[14];
			unsigned char stationCount;

		} FindOptionsSpecific(
			const unsigned char stationId,
			const Station::Type type);

		struct FindOptionsResult
		{
			unsigned char taxiStations[1];
			unsigned char busStations[1];
			unsigned char undergroundStations[1];
			unsigned char ferryStations[1];
		} FindOptions(
			const unsigned char stationId);





		Station GetStationType(
			const unsigned char stationId);
	}
};

RESOURCE_END
