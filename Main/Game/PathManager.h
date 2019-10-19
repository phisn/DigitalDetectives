#pragma once

#include "../Common/Common.h"

#define GAME_START_POSITION_COUNT 18

#pragma pack(push, 1)

namespace Game
{
	struct Station
	{
		enum Type : unsigned char
		{
			Taxi = 0,
			Bus = 1,
			Underground = 2,
			Ferry = 3

		} type : 6; // pad

		unsigned char isFerry : 1;
	};

	struct Connection // 472
	{
		unsigned char station1 : 8;
		unsigned char station2 : 8;

		Station::Type type : 3;
	};

	namespace PathManager
	{
		struct FindRandomStartsResult
		{
			unsigned char starts[GAME_START_POSITION_COUNT];
		};

		FindRandomStartsResult FindRandomStarts();

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
			// plus one as zero byte
			unsigned char taxiStations[6 + 1];
			unsigned char busStations[5 + 1];
			unsigned char undergroundStations[4 + 1];
			unsigned char ferryStations[2 + 1];
		};
		
		FindOptionsResult FindOptions(
			const unsigned char stationId);

		const Game::Station& GetStationType(
			const unsigned char stationId);
	}
};

#pragma pack(pop)
