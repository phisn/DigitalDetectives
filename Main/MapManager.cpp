#include "MapManager.h"

namespace
{
	Game::MapPosition index_map[COMMON_MAP_SIZE] PROGMEM =
	{
		000, 000, 000, 000, 000,   000, 000, 000, 000, 000,
		000, 000, 000, 000, 000,   000, 000, 000, 000, 000,
		000, 000, 000, 000, 000,   000, 000, 000, 000, 000,
		000, 000, 000, 000, 000,   000, 000, 000, 000, 000,
		000, 000, 000, 000, 000,   000, 000, 000, 000, 000,
		000, 000, 000, 000, 000,   000, 000, 000, 000, 000,
		000, 000, 000, 000, 000,   000, 000, 000, 000, 000,
		000, 000, 000, 000, 000,   000, 000, 000, 000, 000,
		000, 000, 000, 000, 000,   000, 000, 000, 000, 000,
		000, 000, 000, 000, 000,   000, 000, 000, 000, 000,
		000, 000, 000, 000, 000,   000, 000, 000, 000, 000,
		000, 000, 000, 000, 000,   000, 000, 000, 000, 000,
		000, 000, 000, 000, 000,   000, 000, 000, 000, 000,
		000, 000, 000, 000, 000,   000, 000, 000, 000, 000,
		000, 000, 000, 000, 000,   000, 000, 000, 000, 000,
		000, 000, 000, 000, 000,   000, 000, 000, 000, 000,
		000, 000, 000, 000, 000,   000, 000, 000, 000, 000,
		000, 000, 000, 000, 000,   000, 000, 000, 000, 000,
		000, 000, 000, 000, 000,   000, 000, 000, 000, 000,
		000, 000, 000, 000, 000,   000, 000, 000, 000
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

			return (Game::MapPosition) pgm_read_byte(index_map + position);
		}
	}
}