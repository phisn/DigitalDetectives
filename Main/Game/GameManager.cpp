#include "GameManager.h"

namespace
{
	Game::Data data;
}

namespace Game
{
	const Game::Data& GetData()
	{
		return data;
	}


}
