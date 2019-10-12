#include "GameManager.h"

namespace Extern
{
	extern Game::GameData* gameData;
}

namespace Game
{
	namespace GameManager
	{
		void Initialize()
		{
		}

		void Create()
		{
		}

		bool Process()
		{
			return false;
		}

		void Restore()
		{
		}

		const GameData* GetData()
		{
			return Extern::gameData;
		}
	}
}
