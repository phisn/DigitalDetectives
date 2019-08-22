#include "Connection.h"

namespace Game
{
#pragma region Data
	Station stations[199] PROGMEM =
	{


		
		Station {Station::Type::UNDERGROUND, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::BUS, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::BUS, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::UNDERGROUND, 0},
		Station {Station::Type::BUS, 0},
		Station {Station::Type::BUS, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::BUS, 0},
		Station {Station::Type::BUS, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::BUS, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::BUS, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::BUS, 0},
		Station {Station::Type::BUS, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::UNDERGROUND, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::BUS, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::BUS, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::BUS, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::BUS, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::BUS, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::UNDERGROUND, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::BUS, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::UNDERGROUND, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::BUS, 0},
		Station {Station::Type::BUS, 0},
		Station {Station::Type::UNDERGROUND, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::BUS, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::BUS, 0},
		Station {Station::Type::BUS, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::UNDERGROUND, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::UNDERGROUND, 0},
		Station {Station::Type::BUS, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::BUS, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::BUS, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::BUS, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::BUS, 0},
		Station {Station::Type::BUS, 1},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::UNDERGROUND, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 1},
		Station {Station::Type::BUS, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::BUS, 0},
		Station {Station::Type::BUS, 0},
		Station {Station::Type::BUS, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::BUS, 0},
		Station {Station::Type::UNDERGROUND, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::BUS, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::BUS, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::UNDERGROUND, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::BUS, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::BUS, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::UNDERGROUND, 0},
		Station {Station::Type::BUS, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::BUS, 0},
		Station {Station::Type::BUS, 1},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::BUS, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::UNDERGROUND, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::BUS, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::BUS, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::BUS, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::BUS, 0},
		Station {Station::Type::UNDERGROUND, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::BUS, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::BUS, 0},
		Station {Station::Type::BUS, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 1},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::TAXI, 0},
		Station {Station::Type::BUS, 0}
	};

	Connection connections[472] PROGMEM =
	{
		Connection { 1, 8, Station::Type::TAXI },
		Connection { 1, 9, Station::Type::TAXI },
		Connection { 1, 58, Station::Type::BUS },
		Connection { 1, 46, Station::Type::BUS },
		Connection { 1, 46, Station::Type::UNDERGROUND },
		Connection { 2, 20, Station::Type::TAXI },
		Connection { 2, 10, Station::Type::TAXI },
		Connection { 3, 11, Station::Type::TAXI },
		Connection { 3, 12, Station::Type::TAXI },
		Connection { 3, 4, Station::Type::TAXI },
		Connection { 3, 22, Station::Type::BUS },
		Connection { 3, 23, Station::Type::BUS },
		Connection { 4, 13, Station::Type::TAXI },
		Connection { 5, 15, Station::Type::TAXI },
		Connection { 5, 16, Station::Type::TAXI },
		Connection { 6, 29, Station::Type::TAXI },
		Connection { 6, 7, Station::Type::TAXI },
		Connection { 7, 17, Station::Type::TAXI },
		Connection { 7, 42, Station::Type::BUS },
		Connection { 8, 18, Station::Type::TAXI },
		Connection { 8, 19, Station::Type::TAXI },
		Connection { 9, 19, Station::Type::TAXI },
		Connection { 9, 20, Station::Type::TAXI },
		Connection { 10, 11, Station::Type::TAXI },
		Connection { 10, 21, Station::Type::TAXI },
		Connection { 10, 34, Station::Type::TAXI },
		Connection { 11, 22, Station::Type::TAXI },
		Connection { 12, 23, Station::Type::TAXI },
		Connection { 13, 23, Station::Type::TAXI },
		Connection { 13, 14, Station::Type::TAXI },
		Connection { 13, 24, Station::Type::TAXI },
		Connection { 13, 23, Station::Type::BUS },
		Connection { 13, 14, Station::Type::BUS },
		Connection { 13, 52, Station::Type::BUS },
		Connection { 13, 46, Station::Type::UNDERGROUND },
		Connection { 13, 67, Station::Type::UNDERGROUND },
		Connection { 13, 89, Station::Type::UNDERGROUND },
		Connection { 14, 15, Station::Type::TAXI },
		Connection { 14, 25, Station::Type::TAXI },
		Connection { 14, 15, Station::Type::BUS },
		Connection { 15, 16, Station::Type::TAXI },
		Connection { 15, 26, Station::Type::TAXI },
		Connection { 15, 28, Station::Type::TAXI },
		Connection { 15, 41, Station::Type::BUS },
		Connection { 15, 29, Station::Type::BUS },
		Connection { 16, 28, Station::Type::TAXI },
		Connection { 16, 29, Station::Type::TAXI },
		Connection { 17, 29, Station::Type::TAXI },
		Connection { 17, 30, Station::Type::TAXI },
		Connection { 18, 31, Station::Type::TAXI },
		Connection { 18, 43, Station::Type::TAXI },
		Connection { 19, 32, Station::Type::TAXI },
		Connection { 20, 33, Station::Type::TAXI },
		Connection { 21, 33, Station::Type::TAXI },
		Connection { 22, 34, Station::Type::TAXI },
		Connection { 22, 23, Station::Type::TAXI },
		Connection { 22, 35, Station::Type::TAXI },
		Connection { 22, 34, Station::Type::BUS },
		Connection { 22, 23, Station::Type::BUS },
		Connection { 22, 65, Station::Type::BUS },
		Connection { 23, 37, Station::Type::TAXI },
		Connection { 23, 67, Station::Type::BUS },
		Connection { 24, 37, Station::Type::TAXI },
		Connection { 24, 38, Station::Type::TAXI },
		Connection { 25, 38, Station::Type::TAXI },
		Connection { 25, 39, Station::Type::TAXI },
		Connection { 26, 39, Station::Type::TAXI },
		Connection { 26, 27, Station::Type::TAXI },
		Connection { 27, 28, Station::Type::TAXI },
		Connection { 27, 40, Station::Type::TAXI },
		Connection { 28, 41, Station::Type::TAXI },
		Connection { 29, 41, Station::Type::TAXI },
		Connection { 29, 42, Station::Type::TAXI },
		Connection { 29, 41, Station::Type::BUS },
		Connection { 29, 42, Station::Type::BUS },
		Connection { 29, 55, Station::Type::BUS },
		Connection { 30, 42, Station::Type::TAXI },
		Connection { 31, 43, Station::Type::TAXI },
		Connection { 31, 44, Station::Type::TAXI },
		Connection { 32, 44, Station::Type::TAXI },
		Connection { 32, 33, Station::Type::TAXI },
		Connection { 32, 45, Station::Type::TAXI },
		Connection { 33, 46, Station::Type::TAXI },
		Connection { 34, 47, Station::Type::TAXI },
		Connection { 34, 48, Station::Type::TAXI },
		Connection { 34, 46, Station::Type::BUS },
		Connection { 34, 63, Station::Type::BUS },
		Connection { 35, 36, Station::Type::TAXI },
		Connection { 35, 48, Station::Type::TAXI },
		Connection { 35, 65, Station::Type::TAXI },
		Connection { 36, 37, Station::Type::TAXI },
		Connection { 36, 49, Station::Type::TAXI },
		Connection { 37, 50, Station::Type::TAXI },
		Connection { 38, 50, Station::Type::TAXI },
		Connection { 38, 51, Station::Type::TAXI },
		Connection { 39, 51, Station::Type::TAXI },
		Connection { 39, 52, Station::Type::TAXI },
		Connection { 40, 52, Station::Type::TAXI },
		Connection { 40, 41, Station::Type::TAXI },
		Connection { 40, 53, Station::Type::TAXI },
		Connection { 41, 54, Station::Type::TAXI },
		Connection { 41, 52, Station::Type::BUS },
		Connection { 41, 87, Station::Type::BUS },
		Connection { 42, 56, Station::Type::TAXI },
		Connection { 42, 72, Station::Type::TAXI },
		Connection { 42, 72, Station::Type::BUS },
		Connection { 43, 57, Station::Type::TAXI },
		Connection { 44, 58, Station::Type::TAXI },
		Connection { 45, 58, Station::Type::TAXI },
		Connection { 45, 60, Station::Type::TAXI },
		Connection { 45, 59, Station::Type::TAXI },
		Connection { 45, 46, Station::Type::TAXI },
		Connection { 46, 47, Station::Type::TAXI },
		Connection { 46, 61, Station::Type::TAXI },
		Connection { 46, 58, Station::Type::BUS },
		Connection { 46, 78, Station::Type::BUS },
		Connection { 46, 74, Station::Type::UNDERGROUND },
		Connection { 46, 79, Station::Type::UNDERGROUND },
		Connection { 47, 62, Station::Type::TAXI },
		Connection { 48, 62, Station::Type::TAXI },
		Connection { 48, 63, Station::Type::TAXI },
		Connection { 49, 50, Station::Type::TAXI },
		Connection { 49, 66, Station::Type::TAXI },
		Connection { 51, 67, Station::Type::TAXI },
		Connection { 51, 52, Station::Type::TAXI },
		Connection { 51, 68, Station::Type::TAXI },
		Connection { 52, 69, Station::Type::TAXI },
		Connection { 52, 67, Station::Type::BUS },
		Connection { 52, 86, Station::Type::BUS },
		Connection { 53, 54, Station::Type::TAXI },
		Connection { 53, 69, Station::Type::TAXI },
		Connection { 54, 55, Station::Type::TAXI },
		Connection { 54, 70, Station::Type::TAXI },
		Connection { 55, 71, Station::Type::TAXI },
		Connection { 55, 89, Station::Type::BUS },
		Connection { 56, 91, Station::Type::TAXI },
		Connection { 57, 58, Station::Type::TAXI },
		Connection { 57, 73, Station::Type::TAXI },
		Connection { 58, 59, Station::Type::TAXI },
		Connection { 58, 74, Station::Type::TAXI },
		Connection { 58, 74, Station::Type::BUS },
		Connection { 58, 75, Station::Type::TAXI },
		Connection { 58, 77, Station::Type::BUS },
		Connection { 59, 75, Station::Type::TAXI },
		Connection { 59, 76, Station::Type::TAXI },
		Connection { 60, 61, Station::Type::TAXI },
		Connection { 60, 76, Station::Type::TAXI },
		Connection { 61, 62, Station::Type::TAXI },
		Connection { 61, 76, Station::Type::TAXI },
		Connection { 61, 78, Station::Type::TAXI },
		Connection { 62, 79, Station::Type::TAXI },
		Connection { 63, 64, Station::Type::TAXI },
		Connection { 63, 80, Station::Type::TAXI },
		Connection { 63, 79, Station::Type::TAXI },
		Connection { 63, 79, Station::Type::BUS },
		Connection { 63, 65, Station::Type::BUS },
		Connection { 63, 100, Station::Type::BUS },
		Connection { 64, 65, Station::Type::TAXI },
		Connection { 64, 81, Station::Type::TAXI },
		Connection { 65, 66, Station::Type::TAXI },
		Connection { 65, 82, Station::Type::TAXI },
		Connection { 65, 67, Station::Type::BUS },
		Connection { 65, 82, Station::Type::BUS },
		Connection { 66, 67, Station::Type::TAXI },
		Connection { 66, 82, Station::Type::TAXI },
		Connection { 67, 68, Station::Type::TAXI },
		Connection { 67, 84, Station::Type::TAXI },
		Connection { 67, 82, Station::Type::BUS },
		Connection { 67, 102, Station::Type::BUS },
		Connection { 67, 79, Station::Type::UNDERGROUND },
		Connection { 67, 111, Station::Type::UNDERGROUND },
		Connection { 67, 89, Station::Type::UNDERGROUND },
		Connection { 68, 69, Station::Type::TAXI },
		Connection { 68, 85, Station::Type::TAXI },
		Connection { 69, 86, Station::Type::TAXI },
		Connection { 70, 71, Station::Type::TAXI },
		Connection { 70, 87, Station::Type::TAXI },
		Connection { 71, 72, Station::Type::TAXI },
		Connection { 71, 89, Station::Type::TAXI },
		Connection { 72, 91, Station::Type::TAXI },
		Connection { 72, 90, Station::Type::TAXI },
		Connection { 72, 105, Station::Type::BUS },
		Connection { 72, 107, Station::Type::BUS },
		Connection { 73, 74, Station::Type::TAXI },
		Connection { 73, 92, Station::Type::TAXI },
		Connection { 74, 92, Station::Type::TAXI },
		Connection { 74, 75, Station::Type::TAXI },
		Connection { 74, 94, Station::Type::BUS },
		Connection { 75, 94, Station::Type::TAXI },
		Connection { 76, 77, Station::Type::TAXI },
		Connection { 77, 78, Station::Type::TAXI },
		Connection { 77, 95, Station::Type::TAXI },
		Connection { 77, 96, Station::Type::TAXI },
		Connection { 77, 94, Station::Type::BUS },
		Connection { 77, 78, Station::Type::BUS },
		Connection { 77, 124, Station::Type::BUS },
		Connection { 78, 79, Station::Type::TAXI },
		Connection { 78, 97, Station::Type::TAXI },
		Connection { 78, 79, Station::Type::BUS },
		Connection { 79, 98, Station::Type::TAXI },
		Connection { 79, 93, Station::Type::UNDERGROUND },
		Connection { 79, 111, Station::Type::UNDERGROUND },
		Connection { 80, 99, Station::Type::TAXI },
		Connection { 80, 100, Station::Type::TAXI },
		Connection { 81, 82, Station::Type::TAXI },
		Connection { 81, 100, Station::Type::TAXI },
		Connection { 82, 101, Station::Type::TAXI },
		Connection { 82, 100, Station::Type::BUS },
		Connection { 82, 140, Station::Type::BUS },
		Connection { 83, 101, Station::Type::TAXI },
		Connection { 83, 102, Station::Type::TAXI },
		Connection { 84, 85, Station::Type::TAXI },
		Connection { 85, 103, Station::Type::TAXI },
		Connection { 86, 103, Station::Type::TAXI },
		Connection { 86, 104, Station::Type::TAXI },
		Connection { 86, 87, Station::Type::BUS },
		Connection { 86, 102, Station::Type::BUS },
		Connection { 86, 116, Station::Type::BUS },
		Connection { 87, 88, Station::Type::TAXI },
		Connection { 87, 105, Station::Type::BUS },
		Connection { 88, 117, Station::Type::TAXI },
		Connection { 88, 89, Station::Type::TAXI },
		Connection { 89, 105, Station::Type::TAXI },
		Connection { 89, 105, Station::Type::BUS },
		Connection { 89, 140, Station::Type::UNDERGROUND },
		Connection { 89, 128, Station::Type::UNDERGROUND },
		Connection { 90, 105, Station::Type::TAXI },
		Connection { 90, 91, Station::Type::TAXI },
		Connection { 91, 105, Station::Type::TAXI },
		Connection { 91, 107, Station::Type::TAXI },
		Connection { 92, 93, Station::Type::TAXI },
		Connection { 93, 94, Station::Type::TAXI },
		Connection { 93, 94, Station::Type::BUS },
		Connection { 94, 95, Station::Type::TAXI },
		Connection { 95, 122, Station::Type::TAXI },
		Connection { 96, 97, Station::Type::TAXI },
		Connection { 96, 109, Station::Type::TAXI },
		Connection { 97, 98, Station::Type::TAXI },
		Connection { 97, 109, Station::Type::TAXI },
		Connection { 98, 99, Station::Type::TAXI },
		Connection { 98, 110, Station::Type::TAXI },
		Connection { 99, 110, Station::Type::TAXI },
		Connection { 99, 112, Station::Type::TAXI },
		Connection { 100, 101, Station::Type::TAXI },
		Connection { 100, 112, Station::Type::TAXI },
		Connection { 100, 113, Station::Type::TAXI },
		Connection { 100, 111, Station::Type::BUS },
		Connection { 101, 114, Station::Type::TAXI },
		Connection { 102, 103, Station::Type::TAXI },
		Connection { 102, 115, Station::Type::TAXI },
		Connection { 102, 127, Station::Type::BUS },
		Connection { 104, 116, Station::Type::TAXI },
		Connection { 105, 106, Station::Type::TAXI },
		Connection { 105, 107, Station::Type::BUS },
		Connection { 105, 108, Station::Type::TAXI },
		Connection { 105, 108, Station::Type::BUS },
		Connection { 106, 107, Station::Type::TAXI },
		Connection { 107, 119, Station::Type::TAXI },
		Connection { 107, 161, Station::Type::BUS },
		Connection { 108, 115, Station::Type::FERRY },
		Connection { 108, 117, Station::Type::TAXI },
		Connection { 108, 116, Station::Type::BUS },
		Connection { 108, 119, Station::Type::TAXI },
		Connection { 108, 135, Station::Type::BUS },
		Connection { 109, 110, Station::Type::TAXI },
		Connection { 109, 124, Station::Type::TAXI },
		Connection { 110, 111, Station::Type::TAXI },
		Connection { 111, 112, Station::Type::TAXI },
		Connection { 111, 124, Station::Type::TAXI },
		Connection { 111, 124, Station::Type::BUS },
		Connection { 111, 153, Station::Type::UNDERGROUND },
		Connection { 111, 163, Station::Type::UNDERGROUND },
		Connection { 112, 125, Station::Type::TAXI },
		Connection { 113, 114, Station::Type::TAXI },
		Connection { 113, 125, Station::Type::TAXI },
		Connection { 114, 115, Station::Type::TAXI },
		Connection { 114, 126, Station::Type::TAXI },
		Connection { 114, 131, Station::Type::TAXI },
		Connection { 114, 132, Station::Type::TAXI },
		Connection { 115, 127, Station::Type::TAXI },
		Connection { 115, 126, Station::Type::TAXI },
		Connection { 115, 157, Station::Type::FERRY },
		Connection { 116, 117, Station::Type::TAXI },
		Connection { 116, 118, Station::Type::TAXI },
		Connection { 116, 127, Station::Type::TAXI },
		Connection { 116, 127, Station::Type::BUS },
		Connection { 116, 142, Station::Type::BUS },
		Connection { 117, 129, Station::Type::TAXI },
		Connection { 118, 129, Station::Type::TAXI },
		Connection { 118, 134, Station::Type::TAXI },
		Connection { 118, 142, Station::Type::TAXI },
		Connection { 119, 136, Station::Type::TAXI },
		Connection { 120, 121, Station::Type::TAXI },
		Connection { 120, 144, Station::Type::TAXI },
		Connection { 121, 122, Station::Type::TAXI },
		Connection { 121, 145, Station::Type::TAXI },
		Connection { 122, 123, Station::Type::TAXI },
		Connection { 122, 146, Station::Type::TAXI },
		Connection { 122, 144, Station::Type::BUS },
		Connection { 122, 123, Station::Type::BUS },
		Connection { 123, 124, Station::Type::TAXI },
		Connection { 123, 137, Station::Type::TAXI },
		Connection { 123, 148, Station::Type::TAXI },
		Connection { 123, 149, Station::Type::TAXI },
		Connection { 123, 144, Station::Type::BUS },
		Connection { 123, 165, Station::Type::BUS },
		Connection { 123, 124, Station::Type::BUS },
		Connection { 124, 138, Station::Type::TAXI },
		Connection { 124, 153, Station::Type::BUS },
		Connection { 124, 130, Station::Type::TAXI },
		Connection { 124, 138, Station::Type::TAXI },
		Connection { 124, 153, Station::Type::BUS },
		Connection { 125, 131, Station::Type::TAXI },
		Connection { 126, 127, Station::Type::TAXI },
		Connection { 126, 140, Station::Type::TAXI },
		Connection { 127, 133, Station::Type::TAXI },
		Connection { 127, 134, Station::Type::TAXI },
		Connection { 127, 133, Station::Type::BUS },
		Connection { 128, 188, Station::Type::TAXI },
		Connection { 128, 185, Station::Type::UNDERGROUND },
		Connection { 128, 199, Station::Type::BUS },
		Connection { 128, 187, Station::Type::BUS },
		Connection { 129, 135, Station::Type::TAXI },
		Connection { 129, 142, Station::Type::TAXI },
		Connection { 129, 143, Station::Type::TAXI },
		Connection { 130, 131, Station::Type::TAXI },
		Connection { 130, 139, Station::Type::TAXI },
		Connection { 132, 140, Station::Type::TAXI },
		Connection { 133, 141, Station::Type::TAXI },
		Connection { 133, 140, Station::Type::TAXI },
		Connection { 133, 140, Station::Type::BUS },
		Connection { 133, 157, Station::Type::BUS },
		Connection { 134, 141, Station::Type::TAXI },
		Connection { 134, 142, Station::Type::TAXI },
		Connection { 135, 136, Station::Type::TAXI },
		Connection { 135, 143, Station::Type::TAXI },
		Connection { 135, 161, Station::Type::TAXI },
		Connection { 135, 128, Station::Type::BUS },
		Connection { 135, 161, Station::Type::BUS },
		Connection { 136, 162, Station::Type::TAXI },
		Connection { 137, 147, Station::Type::TAXI },
		Connection { 138, 150, Station::Type::TAXI },
		Connection { 138, 152, Station::Type::TAXI },
		Connection { 139, 140, Station::Type::TAXI },
		Connection { 139, 154, Station::Type::TAXI },
		Connection { 139, 153, Station::Type::TAXI },
		Connection { 140, 154, Station::Type::TAXI },
		Connection { 140, 156, Station::Type::TAXI },
		Connection { 140, 154, Station::Type::BUS },
		Connection { 140, 156, Station::Type::BUS },
		Connection { 140, 153, Station::Type::UNDERGROUND },
		Connection { 140, 128, Station::Type::UNDERGROUND },
		Connection { 141, 142, Station::Type::TAXI },
		Connection { 141, 158, Station::Type::TAXI },
		Connection { 142, 143, Station::Type::TAXI },
		Connection { 142, 128, Station::Type::TAXI },
		Connection { 142, 158, Station::Type::TAXI },
		Connection { 142, 157, Station::Type::BUS },
		Connection { 142, 128, Station::Type::BUS },
		Connection { 143, 128, Station::Type::TAXI },
		Connection { 143, 160, Station::Type::TAXI },
		Connection { 144, 145, Station::Type::TAXI },
		Connection { 144, 177, Station::Type::TAXI },
		Connection { 144, 163, Station::Type::BUS },
		Connection { 145, 146, Station::Type::TAXI },
		Connection { 146, 147, Station::Type::TAXI },
		Connection { 146, 163, Station::Type::TAXI },
		Connection { 147, 164, Station::Type::TAXI },
		Connection { 148, 149, Station::Type::TAXI },
		Connection { 148, 164, Station::Type::TAXI },
		Connection { 149, 150, Station::Type::TAXI },
		Connection { 149, 165, Station::Type::TAXI },
		Connection { 150, 151, Station::Type::TAXI },
		Connection { 151, 152, Station::Type::TAXI },
		Connection { 151, 165, Station::Type::TAXI },
		Connection { 151, 166, Station::Type::TAXI },
		Connection { 152, 153, Station::Type::TAXI },
		Connection { 153, 154, Station::Type::TAXI },
		Connection { 153, 166, Station::Type::TAXI },
		Connection { 153, 167, Station::Type::TAXI },
		Connection { 153, 154, Station::Type::BUS },
		Connection { 153, 180, Station::Type::BUS },
		Connection { 153, 184, Station::Type::BUS },
		Connection { 153, 163, Station::Type::UNDERGROUND },
		Connection { 153, 185, Station::Type::UNDERGROUND },
		Connection { 154, 155, Station::Type::TAXI },
		Connection { 154, 156, Station::Type::BUS },
		Connection { 155, 167, Station::Type::TAXI },
		Connection { 155, 168, Station::Type::TAXI },
		Connection { 155, 156, Station::Type::TAXI },
		Connection { 156, 157, Station::Type::TAXI },
		Connection { 156, 169, Station::Type::TAXI },
		Connection { 156, 157, Station::Type::BUS },
		Connection { 156, 184, Station::Type::BUS },
		Connection { 157, 158, Station::Type::TAXI },
		Connection { 157, 170, Station::Type::TAXI },
		Connection { 157, 185, Station::Type::BUS },
		Connection { 157, 194, Station::Type::FERRY },
		Connection { 158, 159, Station::Type::TAXI },
		Connection { 159, 170, Station::Type::TAXI },
		Connection { 159, 172, Station::Type::TAXI },
		Connection { 159, 186, Station::Type::TAXI },
		Connection { 159, 198, Station::Type::TAXI },
		Connection { 160, 161, Station::Type::TAXI },
		Connection { 160, 173, Station::Type::TAXI },
		Connection { 160, 128, Station::Type::TAXI },
		Connection { 161, 174, Station::Type::TAXI },
		Connection { 161, 128, Station::Type::BUS },
		Connection { 161, 199, Station::Type::BUS },
		Connection { 162, 175, Station::Type::TAXI },
		Connection { 163, 177, Station::Type::TAXI },
		Connection { 163, 176, Station::Type::BUS },
		Connection { 163, 191, Station::Type::BUS },
		Connection { 164, 178, Station::Type::TAXI },
		Connection { 164, 179, Station::Type::TAXI },
		Connection { 165, 179, Station::Type::TAXI },
		Connection { 165, 180, Station::Type::TAXI },
		Connection { 165, 191, Station::Type::BUS },
		Connection { 165, 180, Station::Type::BUS },
		Connection { 166, 181, Station::Type::TAXI },
		Connection { 166, 183, Station::Type::TAXI },
		Connection { 167, 168, Station::Type::TAXI },
		Connection { 167, 183, Station::Type::TAXI },
		Connection { 168, 184, Station::Type::TAXI },
		Connection { 169, 184, Station::Type::TAXI },
		Connection { 170, 185, Station::Type::TAXI },
		Connection { 171, 173, Station::Type::TAXI },
		Connection { 171, 175, Station::Type::TAXI },
		Connection { 171, 199, Station::Type::TAXI },
		Connection { 172, 187, Station::Type::TAXI },
		Connection { 173, 174, Station::Type::TAXI },
		Connection { 172, 128, Station::Type::TAXI },
		Connection { 173, 188, Station::Type::TAXI },
		Connection { 174, 175, Station::Type::TAXI },
		Connection { 176, 177, Station::Type::TAXI },
		Connection { 176, 189, Station::Type::TAXI },
		Connection { 176, 190, Station::Type::BUS },
		Connection { 178, 189, Station::Type::TAXI },
		Connection { 178, 191, Station::Type::TAXI },
		Connection { 179, 191, Station::Type::TAXI },
		Connection { 180, 181, Station::Type::TAXI },
		Connection { 180, 184, Station::Type::BUS },
		Connection { 180, 193, Station::Type::TAXI },
		Connection { 180, 190, Station::Type::BUS },
		Connection { 181, 193, Station::Type::TAXI },
		Connection { 181, 182, Station::Type::TAXI },
		Connection { 182, 183, Station::Type::TAXI },
		Connection { 182, 195, Station::Type::TAXI },
		Connection { 183, 196, Station::Type::TAXI },
		Connection { 184, 196, Station::Type::TAXI },
		Connection { 184, 185, Station::Type::TAXI },
		Connection { 184, 185, Station::Type::BUS },
		Connection { 184, 197, Station::Type::TAXI },
		Connection { 185, 186, Station::Type::TAXI },
		Connection { 185, 187, Station::Type::BUS },
		Connection { 185, 199, Station::Type::BUS },
		Connection { 186, 198, Station::Type::TAXI },
		Connection { 187, 188, Station::Type::TAXI },
		Connection { 187, 198, Station::Type::TAXI },
		Connection { 187, 199, Station::Type::BUS },
		Connection { 188, 199, Station::Type::TAXI },
		Connection { 189, 190, Station::Type::TAXI },
		Connection { 190, 191, Station::Type::TAXI },
		Connection { 190, 192, Station::Type::TAXI },
		Connection { 190, 191, Station::Type::BUS },
		Connection { 191, 192, Station::Type::TAXI },
		Connection { 192, 194, Station::Type::TAXI },
		Connection { 193, 194, Station::Type::TAXI },
		Connection { 194, 195, Station::Type::TAXI },
		Connection { 195, 197, Station::Type::TAXI },
		Connection { 196, 197, Station::Type::TAXI },
		Connection { 198, 199, Station::Type::TAXI }
	};
#pragma endregion

	Path::FindOptionsSpecificResult Path::FindOptionsSpecific(
		const unsigned char stationId,
		const Station::Type type)
	{
		FindOptionsSpecificResult result{ };

		for (int i = 0; i < 472; ++i)
			if (connections[i].type == type)
			{
				const bool isStation1 = connections[i].station1 == stationId;
				const bool isStation2 = connections[i].station2 == stationId;

				if (isStation1 || isStation2)
				{
					result.station[result.stationCount++] = isStation1
						? connections[i].station2
						: connections[i].station1;

					if (result.stationCount == 14)
					{
						break;
					}
				}
			}

		return result;
	}

	void FindOptionsFillResult(
		const unsigned char stationId,
		const Station::Type type, 
		unsigned char* const result)
	{
		Path::FindOptionsSpecificResult specificResult = Path::FindOptionsSpecific(
			stationId,
			type
		);

		for (int i = 0; i < specificResult.stationCount; ++i)
		{
			result[i] = specificResult.station[i];
		}
	}

	Path::FindOptionsResult Path::FindOptions(
		const unsigned char stationId)
	{
		FindOptionsResult result{ };

		FindOptionsFillResult(stationId, Station::Type::TAXI, result.taxiStations);
		FindOptionsFillResult(stationId, Station::Type::BUS, result.busStations);
		FindOptionsFillResult(stationId, Station::Type::UNDERGROUND, result.undergroundStations);
		FindOptionsFillResult(stationId, Station::Type::FERRY, result.ferryStations);

		return result;
	}

	const Station& Game::Path::GetStationType(
		const unsigned char stationId)
	{
		return stations[stationId];
	}
}
