#pragma once

#include "../Common/Common.h"

#pragma pack(push, 1)

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
			unsigned char station[6]; // highest possible number
			unsigned char stationCount;

		};
		
		FindOptionsSpecificResult FindOptionsSpecific(
			const unsigned char stationId,
			const Station::Type type);

		struct FindOptionsResult
		{
			unsigned char taxiStations[6];
			unsigned char busStations[5];
			unsigned char undergroundStations[4];
			unsigned char ferryStations[2];

		};
		
		FindOptionsResult FindOptions(
			const unsigned char stationId);

		const Game::Station& GetStationType(
			const unsigned char stationId);
	}
};

#pragma pack(pop)
