#include "MapManager.h"

namespace
{
	Game::MapPosition index_map[COMMON_MAP_SIZE] PROGMEM =
	{
		190, 191, 192, 193, 194,   182, 195, 196, 197, 184,
		185, 186, 198, 187, 199,   188, 173, 171, 175, 189,
		178, 179, 180, 181, 166,   183, 167, 168, 169, 170,
		159, 172, 128, 160, 174,   176, 177, 163, 164, 148,
		165, 151, 153, 154, 155,   156, 157, 158, 142, 143,
		161, 162, 144, 145, 146,   147, 137, 149, 150, 138,
		152, 139, 140, 133, 141,   134, 118, 129, 153, 136,
		120, 121, 122, 123, 124,   130, 125, 131, 113, 132,
		114, 126, 127, 116, 117,   108, 119, 109, 111, 112,
		100, 101, 115,  92,  93,    94,  94,  96,  97,  98,
		110,  99,  80,  81,  82,    83, 102, 103,  86, 104,
		 87,  88,  89, 105, 106,   107,  73,  74,  75,  59,
		 76,  77,  78,  79,  63,    64,  65,  66,  67,  84,
		 68,  85,  69,  53,  70,    71,  90,  91,  57,  58,
		 45,  60,  46,  61,  62,    48,  35,  36,  49,  50,
		 51,  52,  40,  54,  55,    72,  56,  43,  31,  44,
		 32,  33,  21,  47,  34,    22,  23,  37,  24,  38,
		 39,  27,  28,  41,  29,    42,  30,  18,  19,  20,
		 10,  11,  12,  13,  25,    26,  16,  17,   8,   1,
		  9,   2,   3,   4,  14,    15,   5,   6,   7
	};
}

namespace Device
{
	namespace MapManager
	{
		void Initialize()
		{
		}

		void Unintialize()
		{
		}

		Game::MapPosition Translate(const Game::MapPosition position)
		{
			static_assert(sizeof(Game::MapPosition) == 1, 
				"Position size changed, need to adopt 'Translate'");

			for (int i = 0; i < COMMON_MAP_SIZE; ++i)
				if (pgm_read_byte(index_map + i) == position)
				{
					return (Game::MapPosition) i;
				}

			// return (Game::MapPosition) pgm_read_byte(index_map + position);
		}
	}
}
