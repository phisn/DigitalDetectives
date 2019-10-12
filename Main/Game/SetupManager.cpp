#include "SetupManager.h"

namespace Extern
{
	extern Game::SetupData* setupData;
}

namespace Game
{
	namespace SetupManager
	{
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

		const Game::SetupData* GetData()
		{
			return Extern::setupData;
		}
	}
}
