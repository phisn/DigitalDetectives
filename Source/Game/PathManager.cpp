#include "PathManager.h"

namespace Game
{
#pragma region Data
	Station stations[] PROGMEM =
	{
		Station {Station::Type::Underground, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Bus, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Bus, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Underground, 0},
		Station {Station::Type::Bus, 0},
		Station {Station::Type::Bus, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Bus, 0},
		Station {Station::Type::Bus, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Bus, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Bus, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Bus, 0},
		Station {Station::Type::Bus, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Underground, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Bus, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Bus, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Bus, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Bus, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Bus, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Underground, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Bus, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Underground, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Bus, 0},
		Station {Station::Type::Bus, 0},
		Station {Station::Type::Underground, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Bus, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Bus, 0},
		Station {Station::Type::Bus, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Underground, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Underground, 0},
		Station {Station::Type::Bus, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Bus, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Bus, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Bus, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Bus, 0},
		Station {Station::Type::Bus, 1},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Underground, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 1},
		Station {Station::Type::Bus, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Bus, 0},
		Station {Station::Type::Bus, 0},
		Station {Station::Type::Bus, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Bus, 0},
		Station {Station::Type::Underground, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Bus, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Bus, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Underground, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Bus, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Bus, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Underground, 0},
		Station {Station::Type::Bus, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Bus, 0},
		Station {Station::Type::Bus, 1},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Bus, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Underground, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Bus, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Bus, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Bus, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Bus, 0},
		Station {Station::Type::Underground, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Bus, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Bus, 0},
		Station {Station::Type::Bus, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 1},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Taxi, 0},
		Station {Station::Type::Bus, 0}
	};

	Connection connections[] PROGMEM =
	{
		Connection { 1, 8, Station::Type::Taxi },
		Connection { 1, 9, Station::Type::Taxi },
		Connection { 1, 58, Station::Type::Bus },
		Connection { 1, 46, Station::Type::Bus },
		Connection { 1, 46, Station::Type::Underground },

		Connection { 2, 20, Station::Type::Taxi },
		Connection { 2, 10, Station::Type::Taxi },
		
		Connection { 3, 11, Station::Type::Taxi },
		Connection { 3, 12, Station::Type::Taxi },
		Connection { 3, 4, Station::Type::Taxi },
		Connection { 3, 22, Station::Type::Bus },
		Connection { 3, 23, Station::Type::Bus },
		
		Connection { 4, 13, Station::Type::Taxi },
		
		Connection { 5, 15, Station::Type::Taxi },
		Connection { 5, 16, Station::Type::Taxi },
		
		Connection { 6, 29, Station::Type::Taxi },
		Connection { 6, 7, Station::Type::Taxi },
		
		Connection { 7, 17, Station::Type::Taxi },
		Connection { 7, 42, Station::Type::Bus },
		
		Connection { 8, 18, Station::Type::Taxi },
		Connection { 8, 19, Station::Type::Taxi },
		
		Connection { 9, 19, Station::Type::Taxi },
		Connection { 9, 20, Station::Type::Taxi },
		
		Connection { 10, 11, Station::Type::Taxi },
		Connection { 10, 21, Station::Type::Taxi },
		Connection { 10, 34, Station::Type::Taxi },
		
		Connection { 11, 22, Station::Type::Taxi },
		
		Connection { 12, 23, Station::Type::Taxi },
		
		Connection { 13, 23, Station::Type::Taxi },
		Connection { 13, 14, Station::Type::Taxi },
		Connection { 13, 24, Station::Type::Taxi },
		Connection { 13, 23, Station::Type::Bus },
		Connection { 13, 14, Station::Type::Bus },
		Connection { 13, 52, Station::Type::Bus },
		Connection { 13, 46, Station::Type::Underground },
		Connection { 13, 67, Station::Type::Underground },
		Connection { 13, 89, Station::Type::Underground },
		
		Connection { 14, 15, Station::Type::Taxi },
		Connection { 14, 25, Station::Type::Taxi },
		Connection { 14, 15, Station::Type::Bus },
		
		Connection { 15, 16, Station::Type::Taxi },
		Connection { 15, 26, Station::Type::Taxi },
		Connection { 15, 28, Station::Type::Taxi },
		Connection { 15, 41, Station::Type::Bus },
		Connection { 15, 29, Station::Type::Bus },
		
		Connection { 16, 28, Station::Type::Taxi },
		Connection { 16, 29, Station::Type::Taxi },
		
		Connection { 17, 29, Station::Type::Taxi },
		Connection { 17, 30, Station::Type::Taxi },
		
		Connection { 18, 31, Station::Type::Taxi },
		Connection { 18, 43, Station::Type::Taxi },
		
		Connection { 19, 32, Station::Type::Taxi },
		
		Connection { 20, 33, Station::Type::Taxi },

		Connection { 21, 33, Station::Type::Taxi },

		Connection { 22, 34, Station::Type::Taxi },
		Connection { 22, 23, Station::Type::Taxi },
		Connection { 22, 35, Station::Type::Taxi },
		Connection { 22, 34, Station::Type::Bus },
		Connection { 22, 23, Station::Type::Bus },
		Connection { 22, 65, Station::Type::Bus },
		
		Connection { 23, 37, Station::Type::Taxi },
		Connection { 23, 67, Station::Type::Bus },
		
		Connection { 24, 37, Station::Type::Taxi },
		Connection { 24, 38, Station::Type::Taxi },
		
		Connection { 25, 38, Station::Type::Taxi },
		Connection { 25, 39, Station::Type::Taxi },
		
		Connection { 26, 39, Station::Type::Taxi },
		Connection { 26, 27, Station::Type::Taxi },
		
		Connection { 27, 28, Station::Type::Taxi },
		Connection { 27, 40, Station::Type::Taxi },
		
		Connection { 28, 41, Station::Type::Taxi },
		
		Connection { 29, 41, Station::Type::Taxi },
		Connection { 29, 42, Station::Type::Taxi },
		Connection { 29, 41, Station::Type::Bus },
		Connection { 29, 42, Station::Type::Bus },
		Connection { 29, 55, Station::Type::Bus },
		
		Connection { 30, 42, Station::Type::Taxi },

		Connection { 31, 43, Station::Type::Taxi },
		Connection { 31, 44, Station::Type::Taxi },

		Connection { 32, 44, Station::Type::Taxi },
		Connection { 32, 33, Station::Type::Taxi },
		Connection { 32, 45, Station::Type::Taxi },
	
		Connection { 33, 46, Station::Type::Taxi },

		Connection { 34, 47, Station::Type::Taxi },
		Connection { 34, 48, Station::Type::Taxi },
		Connection { 34, 46, Station::Type::Bus },
		Connection { 34, 63, Station::Type::Bus },
		
		Connection { 35, 36, Station::Type::Taxi },
		Connection { 35, 48, Station::Type::Taxi },
		Connection { 35, 65, Station::Type::Taxi },
		
		Connection { 36, 37, Station::Type::Taxi },
		Connection { 36, 49, Station::Type::Taxi },
		
		Connection { 37, 50, Station::Type::Taxi },
		
		Connection { 38, 50, Station::Type::Taxi },
		Connection { 38, 51, Station::Type::Taxi },
		
		Connection { 39, 51, Station::Type::Taxi },
		Connection { 39, 52, Station::Type::Taxi },
	
		Connection { 40, 52, Station::Type::Taxi },
		Connection { 40, 41, Station::Type::Taxi },
		Connection { 40, 53, Station::Type::Taxi },
		
		Connection { 41, 54, Station::Type::Taxi },
		Connection { 41, 52, Station::Type::Bus },
		Connection { 41, 87, Station::Type::Bus },
		
		Connection { 42, 56, Station::Type::Taxi },
		Connection { 42, 72, Station::Type::Taxi },
		Connection { 42, 72, Station::Type::Bus },

		Connection { 43, 57, Station::Type::Taxi },

		Connection { 44, 58, Station::Type::Taxi },

		Connection { 45, 58, Station::Type::Taxi },
		Connection { 45, 60, Station::Type::Taxi },
		Connection { 45, 59, Station::Type::Taxi },
		Connection { 45, 46, Station::Type::Taxi },

		Connection { 46, 47, Station::Type::Taxi },
		Connection { 46, 61, Station::Type::Taxi },
		Connection { 46, 58, Station::Type::Bus },
		Connection { 46, 78, Station::Type::Bus },
		Connection { 46, 74, Station::Type::Underground },
		Connection { 46, 79, Station::Type::Underground },

		Connection { 47, 62, Station::Type::Taxi },

		Connection { 48, 62, Station::Type::Taxi },
		Connection { 48, 63, Station::Type::Taxi },

		Connection { 49, 50, Station::Type::Taxi },
		Connection { 49, 66, Station::Type::Taxi },

		Connection { 51, 67, Station::Type::Taxi },
		Connection { 51, 52, Station::Type::Taxi },
		Connection { 51, 68, Station::Type::Taxi },

		Connection { 52, 69, Station::Type::Taxi },
		Connection { 52, 67, Station::Type::Bus },
		Connection { 52, 86, Station::Type::Bus },

		Connection { 53, 54, Station::Type::Taxi },
		Connection { 53, 69, Station::Type::Taxi },

		Connection { 54, 55, Station::Type::Taxi },
		Connection { 54, 70, Station::Type::Taxi },

		Connection { 55, 71, Station::Type::Taxi },
		Connection { 55, 89, Station::Type::Bus },

		Connection { 56, 91, Station::Type::Taxi },

		Connection { 57, 58, Station::Type::Taxi },
		Connection { 57, 73, Station::Type::Taxi },

		Connection { 58, 59, Station::Type::Taxi },
		Connection { 58, 74, Station::Type::Taxi },
		Connection { 58, 74, Station::Type::Bus },
		Connection { 58, 75, Station::Type::Taxi },
		Connection { 58, 77, Station::Type::Bus },

		Connection { 59, 75, Station::Type::Taxi },
		Connection { 59, 76, Station::Type::Taxi },

		Connection { 60, 61, Station::Type::Taxi },
		Connection { 60, 76, Station::Type::Taxi },

		Connection { 61, 62, Station::Type::Taxi },
		Connection { 61, 76, Station::Type::Taxi },
		Connection { 61, 78, Station::Type::Taxi },

		Connection { 62, 79, Station::Type::Taxi },

		Connection { 63, 64, Station::Type::Taxi },
		Connection { 63, 80, Station::Type::Taxi },
		Connection { 63, 79, Station::Type::Taxi },
		Connection { 63, 79, Station::Type::Bus },
		Connection { 63, 65, Station::Type::Bus },
		Connection { 63, 100, Station::Type::Bus },

		Connection { 64, 65, Station::Type::Taxi },
		Connection { 64, 81, Station::Type::Taxi },

		Connection { 65, 66, Station::Type::Taxi },
		Connection { 65, 82, Station::Type::Taxi },
		Connection { 65, 67, Station::Type::Bus },
		Connection { 65, 82, Station::Type::Bus },

		Connection { 66, 67, Station::Type::Taxi },
		Connection { 66, 82, Station::Type::Taxi },

		Connection { 67, 68, Station::Type::Taxi },
		Connection { 67, 84, Station::Type::Taxi },
		Connection { 67, 82, Station::Type::Bus },
		Connection { 67, 102, Station::Type::Bus },
		Connection { 67, 79, Station::Type::Underground },
		Connection { 67, 111, Station::Type::Underground },
		Connection { 67, 89, Station::Type::Underground },

		Connection { 68, 69, Station::Type::Taxi },
		Connection { 68, 85, Station::Type::Taxi },

		Connection { 69, 86, Station::Type::Taxi },

		Connection { 70, 71, Station::Type::Taxi },
		Connection { 70, 87, Station::Type::Taxi },

		Connection { 71, 72, Station::Type::Taxi },
		Connection { 71, 89, Station::Type::Taxi },

		Connection { 72, 91, Station::Type::Taxi },
		Connection { 72, 90, Station::Type::Taxi },
		Connection { 72, 105, Station::Type::Bus },
		Connection { 72, 107, Station::Type::Bus },

		Connection { 73, 74, Station::Type::Taxi },
		Connection { 73, 92, Station::Type::Taxi },

		Connection { 74, 92, Station::Type::Taxi },
		Connection { 74, 75, Station::Type::Taxi },
		Connection { 74, 94, Station::Type::Bus },

		Connection { 75, 94, Station::Type::Taxi },

		Connection { 76, 77, Station::Type::Taxi },

		Connection { 77, 78, Station::Type::Taxi },
		Connection { 77, 95, Station::Type::Taxi },
		Connection { 77, 96, Station::Type::Taxi },
		Connection { 77, 94, Station::Type::Bus },
		Connection { 77, 78, Station::Type::Bus },
		Connection { 77, 124, Station::Type::Bus },

		Connection { 78, 79, Station::Type::Taxi },
		Connection { 78, 97, Station::Type::Taxi },
		Connection { 78, 79, Station::Type::Bus },

		Connection { 79, 98, Station::Type::Taxi },
		Connection { 79, 93, Station::Type::Underground },
		Connection { 79, 111, Station::Type::Underground },

		Connection { 80, 99, Station::Type::Taxi },
		Connection { 80, 100, Station::Type::Taxi },

		Connection { 81, 82, Station::Type::Taxi },
		Connection { 81, 100, Station::Type::Taxi },

		Connection { 82, 101, Station::Type::Taxi },
		Connection { 82, 100, Station::Type::Bus },
		Connection { 82, 140, Station::Type::Bus },

		Connection { 83, 101, Station::Type::Taxi },
		Connection { 83, 102, Station::Type::Taxi },

		Connection { 84, 85, Station::Type::Taxi },

		Connection { 85, 103, Station::Type::Taxi },

		Connection { 86, 103, Station::Type::Taxi },
		Connection { 86, 104, Station::Type::Taxi },
		Connection { 86, 87, Station::Type::Bus },
		Connection { 86, 102, Station::Type::Bus },
		Connection { 86, 116, Station::Type::Bus },

		Connection { 87, 88, Station::Type::Taxi },
		Connection { 87, 105, Station::Type::Bus },

		Connection { 88, 117, Station::Type::Taxi },
		Connection { 88, 89, Station::Type::Taxi },
		
		Connection { 89, 105, Station::Type::Taxi },
		Connection { 89, 105, Station::Type::Bus },
		Connection { 89, 140, Station::Type::Underground },
		Connection { 89, 128, Station::Type::Underground },
		
		Connection { 90, 105, Station::Type::Taxi },
		Connection { 90, 91, Station::Type::Taxi },

		Connection { 91, 105, Station::Type::Taxi },
		Connection { 91, 107, Station::Type::Taxi },

		Connection { 92, 93, Station::Type::Taxi },

		Connection { 93, 94, Station::Type::Taxi },
		Connection { 93, 94, Station::Type::Bus },

		Connection { 94, 95, Station::Type::Taxi },

		Connection { 95, 122, Station::Type::Taxi },

		Connection { 96, 97, Station::Type::Taxi },
		Connection { 96, 109, Station::Type::Taxi },

		Connection { 97, 98, Station::Type::Taxi },
		Connection { 97, 109, Station::Type::Taxi },

		Connection { 98, 99, Station::Type::Taxi },
		Connection { 98, 110, Station::Type::Taxi },

		Connection { 99, 110, Station::Type::Taxi },
		Connection { 99, 112, Station::Type::Taxi },

		Connection { 100, 101, Station::Type::Taxi },
		Connection { 100, 112, Station::Type::Taxi },
		Connection { 100, 113, Station::Type::Taxi },
		Connection { 100, 111, Station::Type::Bus },

		Connection { 101, 114, Station::Type::Taxi },

		Connection { 102, 103, Station::Type::Taxi },
		Connection { 102, 115, Station::Type::Taxi },
		Connection { 102, 127, Station::Type::Bus },

		Connection { 104, 116, Station::Type::Taxi },

		Connection { 105, 106, Station::Type::Taxi },
		Connection { 105, 107, Station::Type::Bus },
		Connection { 105, 108, Station::Type::Taxi },
		Connection { 105, 108, Station::Type::Bus },

		Connection { 106, 107, Station::Type::Taxi },

		Connection { 107, 119, Station::Type::Taxi },
		Connection { 107, 161, Station::Type::Bus },

		Connection { 108, 115, Station::Type::Ferry },
		Connection { 108, 117, Station::Type::Taxi },
		Connection { 108, 116, Station::Type::Bus },
		Connection { 108, 119, Station::Type::Taxi },
		Connection { 108, 135, Station::Type::Bus },

		Connection { 109, 110, Station::Type::Taxi },
		Connection { 109, 124, Station::Type::Taxi },

		Connection { 110, 111, Station::Type::Taxi },

		Connection { 111, 112, Station::Type::Taxi },
		Connection { 111, 124, Station::Type::Taxi },
		Connection { 111, 124, Station::Type::Bus },
		Connection { 111, 153, Station::Type::Underground },
		Connection { 111, 163, Station::Type::Underground },

		Connection { 112, 125, Station::Type::Taxi },

		Connection { 113, 114, Station::Type::Taxi },
		Connection { 113, 125, Station::Type::Taxi },

		Connection { 114, 115, Station::Type::Taxi },
		Connection { 114, 126, Station::Type::Taxi },
		Connection { 114, 131, Station::Type::Taxi },
		Connection { 114, 132, Station::Type::Taxi },

		Connection { 115, 127, Station::Type::Taxi },
		Connection { 115, 126, Station::Type::Taxi },
		Connection { 115, 157, Station::Type::Ferry },

		Connection { 116, 117, Station::Type::Taxi },
		Connection { 116, 118, Station::Type::Taxi },
		Connection { 116, 127, Station::Type::Taxi },
		Connection { 116, 127, Station::Type::Bus },
		Connection { 116, 142, Station::Type::Bus },

		Connection { 117, 129, Station::Type::Taxi },

		Connection { 118, 129, Station::Type::Taxi },
		Connection { 118, 134, Station::Type::Taxi },
		Connection { 118, 142, Station::Type::Taxi },

		Connection { 119, 136, Station::Type::Taxi },

		Connection { 120, 121, Station::Type::Taxi },
		Connection { 120, 144, Station::Type::Taxi },

		Connection { 121, 122, Station::Type::Taxi },
		Connection { 121, 145, Station::Type::Taxi },

		Connection { 122, 123, Station::Type::Taxi },
		Connection { 122, 146, Station::Type::Taxi },
		Connection { 122, 144, Station::Type::Bus },
		Connection { 122, 123, Station::Type::Bus },

		Connection { 123, 124, Station::Type::Taxi },
		Connection { 123, 137, Station::Type::Taxi },
		Connection { 123, 148, Station::Type::Taxi },
		Connection { 123, 149, Station::Type::Taxi },
		Connection { 123, 144, Station::Type::Bus },
		Connection { 123, 165, Station::Type::Bus },
		Connection { 123, 124, Station::Type::Bus },

		Connection { 124, 138, Station::Type::Taxi },
		Connection { 124, 153, Station::Type::Bus },
		Connection { 124, 130, Station::Type::Taxi },

		Connection { 125, 131, Station::Type::Taxi },

		Connection { 126, 127, Station::Type::Taxi },
		Connection { 126, 140, Station::Type::Taxi },

		Connection { 127, 133, Station::Type::Taxi },
		Connection { 127, 134, Station::Type::Taxi },
		Connection { 127, 133, Station::Type::Bus },

		Connection { 128, 188, Station::Type::Taxi },
		Connection { 128, 172, Station::Type::Taxi },
		Connection { 128, 160, Station::Type::Taxi },
		Connection { 128, 143, Station::Type::Taxi },
		Connection { 128, 142, Station::Type::Taxi },
		Connection { 128, 185, Station::Type::Underground },
		Connection { 128, 140, Station::Type::Underground },
		Connection { 128, 199, Station::Type::Bus },
		Connection { 128, 135, Station::Type::Bus },
		Connection { 128, 187, Station::Type::Bus },
		Connection { 128, 142, Station::Type::Bus },
		Connection { 128, 161, Station::Type::Bus },

		Connection { 129, 135, Station::Type::Taxi },
		Connection { 129, 142, Station::Type::Taxi },
		Connection { 129, 143, Station::Type::Taxi },

		Connection { 130, 131, Station::Type::Taxi },
		Connection { 130, 139, Station::Type::Taxi },

		Connection { 132, 140, Station::Type::Taxi },

		Connection { 133, 141, Station::Type::Taxi },
		Connection { 133, 140, Station::Type::Taxi },
		Connection { 133, 140, Station::Type::Bus },
		Connection { 133, 157, Station::Type::Bus },

		Connection { 134, 141, Station::Type::Taxi },
		Connection { 134, 142, Station::Type::Taxi },

		Connection { 135, 136, Station::Type::Taxi },
		Connection { 135, 143, Station::Type::Taxi },
		Connection { 135, 161, Station::Type::Taxi },

		Connection { 136, 162, Station::Type::Taxi },

		Connection { 137, 147, Station::Type::Taxi },

		Connection { 138, 150, Station::Type::Taxi },
		Connection { 138, 152, Station::Type::Taxi },

		Connection { 139, 140, Station::Type::Taxi },
		Connection { 139, 154, Station::Type::Taxi },
		Connection { 139, 153, Station::Type::Taxi },

		Connection { 140, 154, Station::Type::Taxi },
		Connection { 140, 156, Station::Type::Taxi },
		Connection { 140, 154, Station::Type::Bus },
		Connection { 140, 156, Station::Type::Bus },
		Connection { 140, 153, Station::Type::Underground },

		Connection { 141, 142, Station::Type::Taxi },
		Connection { 141, 158, Station::Type::Taxi },

		Connection { 142, 143, Station::Type::Taxi },
		Connection { 142, 158, Station::Type::Taxi }, // dosent work 
		Connection { 142, 157, Station::Type::Bus },

		Connection { 143, 160, Station::Type::Taxi },

		Connection { 144, 145, Station::Type::Taxi },
		Connection { 144, 177, Station::Type::Taxi },
		Connection { 144, 163, Station::Type::Bus },

		Connection { 145, 146, Station::Type::Taxi },

		Connection { 146, 147, Station::Type::Taxi },
		Connection { 146, 163, Station::Type::Taxi },

		Connection { 147, 164, Station::Type::Taxi },

		Connection { 148, 149, Station::Type::Taxi },
		Connection { 148, 164, Station::Type::Taxi },

		Connection { 149, 150, Station::Type::Taxi },
		Connection { 149, 165, Station::Type::Taxi },

		Connection { 150, 151, Station::Type::Taxi },

		Connection { 151, 152, Station::Type::Taxi },
		Connection { 151, 165, Station::Type::Taxi },
		Connection { 151, 166, Station::Type::Taxi },

		Connection { 152, 153, Station::Type::Taxi },

		Connection { 153, 154, Station::Type::Taxi },
		Connection { 153, 166, Station::Type::Taxi },
		Connection { 153, 167, Station::Type::Taxi },
		Connection { 153, 154, Station::Type::Bus },
		Connection { 153, 180, Station::Type::Bus },
		Connection { 153, 184, Station::Type::Bus },
		Connection { 153, 163, Station::Type::Underground },
		Connection { 153, 185, Station::Type::Underground },

		Connection { 154, 155, Station::Type::Taxi },
		Connection { 154, 156, Station::Type::Bus },

		Connection { 155, 167, Station::Type::Taxi },
		Connection { 155, 168, Station::Type::Taxi },
		Connection { 155, 156, Station::Type::Taxi },

		Connection { 156, 157, Station::Type::Taxi },
		Connection { 156, 169, Station::Type::Taxi },
		Connection { 156, 157, Station::Type::Bus },
		Connection { 156, 184, Station::Type::Bus },

		Connection { 157, 158, Station::Type::Taxi },
		Connection { 157, 170, Station::Type::Taxi },
		Connection { 157, 185, Station::Type::Bus },
		Connection { 157, 194, Station::Type::Ferry },

		Connection { 158, 159, Station::Type::Taxi },

		Connection { 159, 170, Station::Type::Taxi },
		Connection { 159, 172, Station::Type::Taxi },
		Connection { 159, 186, Station::Type::Taxi },
		Connection { 159, 198, Station::Type::Taxi },

		Connection { 160, 161, Station::Type::Taxi },
		Connection { 160, 173, Station::Type::Taxi },

		Connection { 161, 174, Station::Type::Taxi },
		Connection { 161, 199, Station::Type::Bus },

		Connection { 162, 175, Station::Type::Taxi },

		Connection { 163, 177, Station::Type::Taxi },
		Connection { 163, 176, Station::Type::Bus },
		Connection { 163, 191, Station::Type::Bus },

		Connection { 164, 178, Station::Type::Taxi },
		Connection { 164, 179, Station::Type::Taxi },

		Connection { 165, 179, Station::Type::Taxi },
		Connection { 165, 180, Station::Type::Taxi },
		Connection { 165, 191, Station::Type::Bus },
		Connection { 165, 180, Station::Type::Bus },

		Connection { 166, 181, Station::Type::Taxi },
		Connection { 166, 183, Station::Type::Taxi },

		Connection { 167, 168, Station::Type::Taxi },
		Connection { 167, 183, Station::Type::Taxi },

		Connection { 168, 184, Station::Type::Taxi },

		Connection { 169, 184, Station::Type::Taxi },

		Connection { 170, 185, Station::Type::Taxi },

		Connection { 171, 173, Station::Type::Taxi },
		Connection { 171, 175, Station::Type::Taxi },
		Connection { 171, 199, Station::Type::Taxi },

		Connection { 172, 187, Station::Type::Taxi },

		Connection { 173, 174, Station::Type::Taxi },
		Connection { 173, 188, Station::Type::Taxi },

		Connection { 174, 175, Station::Type::Taxi },

		Connection { 176, 177, Station::Type::Taxi },
		Connection { 176, 189, Station::Type::Taxi },
		Connection { 176, 190, Station::Type::Bus },

		Connection { 178, 189, Station::Type::Taxi },
		Connection { 178, 191, Station::Type::Taxi },

		Connection { 179, 191, Station::Type::Taxi },

		Connection { 180, 181, Station::Type::Taxi },
		Connection { 180, 184, Station::Type::Bus },
		Connection { 180, 193, Station::Type::Taxi },
		Connection { 180, 190, Station::Type::Bus },

		Connection { 181, 193, Station::Type::Taxi },
		Connection { 181, 182, Station::Type::Taxi },

		Connection { 182, 183, Station::Type::Taxi },
		Connection { 182, 195, Station::Type::Taxi },

		Connection { 183, 196, Station::Type::Taxi },

		Connection { 184, 196, Station::Type::Taxi },
		Connection { 184, 185, Station::Type::Taxi },
		Connection { 184, 185, Station::Type::Bus },
		Connection { 184, 197, Station::Type::Taxi },

		Connection { 185, 186, Station::Type::Taxi },
		Connection { 185, 187, Station::Type::Bus },

		Connection { 186, 198, Station::Type::Taxi },

		Connection { 187, 188, Station::Type::Taxi },
		Connection { 187, 198, Station::Type::Taxi },

		Connection { 188, 199, Station::Type::Taxi },

		Connection { 189, 190, Station::Type::Taxi },

		Connection { 190, 191, Station::Type::Taxi },
		Connection { 190, 192, Station::Type::Taxi },
		Connection { 190, 191, Station::Type::Bus },

		Connection { 191, 192, Station::Type::Taxi },

		Connection { 192, 194, Station::Type::Taxi },

		Connection { 193, 194, Station::Type::Taxi },

		Connection { 194, 195, Station::Type::Taxi },

		Connection { 195, 197, Station::Type::Taxi },

		Connection { 196, 197, Station::Type::Taxi },

		Connection { 198, 199, Station::Type::Taxi }
	};

	static_assert(sizeof(connections) / sizeof(*connections) == 467,
		"Connections size has changed, adjustment to pathfinder algorithm needed");
	static_assert(sizeof(stations) / sizeof(*stations) == 199,
		"Stations size has changed, adjustment to pathfinder algorithm needed");


	MapPosition starts[GAME_START_POSITION_COUNT] PROGMEM =
	{
		103, 112, 34,
		155, 94, 117,
		132, 53, 174,
		198, 50, 91,
		26, 29, 141,
		13, 138, 197
	};

#pragma endregion

	PathManager::FindRandomStartsResult PathManager::FindRandomStarts()
	{
		FindRandomStartsResult result;
		
		memcpy_P(
			result.starts, 
			starts, 
			GAME_START_POSITION_COUNT * sizeof(MapPosition));

		for (int i = 0; i < GAME_START_POSITION_COUNT; ++i)
		{
			const int randomIndex = random(GAME_START_POSITION_COUNT);

			MapPosition temp = result.starts[i];
			result.starts[i] = result.starts[randomIndex];
			result.starts[randomIndex] = temp;
		}

		return result;
	}

	PathManager::FindOptionsSpecificResult PathManager::FindOptionsSpecific(
		const unsigned char stationId,
		const Station::Type type)
	{
		FindOptionsSpecificResult result{ };

		// speedup possible: only search until stationId,
		// because stations always only contain higher connections
		// -> higher connection can not have stationId
		for (int i = 0; i < 467; ++i)
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
		PathManager::FindOptionsSpecificResult specificResult = PathManager::FindOptionsSpecific(
			stationId,
			type
		);

		for (int i = 0; i < specificResult.stationCount; ++i)
		{
			result[i] = specificResult.station[i];
		}
	}

	PathManager::FindOptionsResult PathManager::FindOptions(
		const unsigned char stationId)
	{
		FindOptionsResult result{ };

		FindOptionsFillResult(stationId, Station::Type::Taxi, result.taxiStations);
		FindOptionsFillResult(stationId, Station::Type::Bus, result.busStations);
		FindOptionsFillResult(stationId, Station::Type::Underground, result.undergroundStations);
		FindOptionsFillResult(stationId, Station::Type::Ferry, result.ferryStations);

		return result;
	}

	const Station& Game::PathManager::GetStationType(
		const unsigned char stationId)
	{
		return stations[stationId - 1];
	}
}
