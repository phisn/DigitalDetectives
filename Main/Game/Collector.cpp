#include "Collector.h"

namespace Extern
{
	extern Game::CollectData* collectData;
}

namespace
{
	bool isRestore = false;
}

namespace Game
{
	namespace Collector
	{
		void Create()
		{
			if (!isRestore)
			{
				Extern::collectData->context.playerCount = 0;
			}
		}

		void Process()
		{
			if (isRestore)
			{

			}
			else
			{


			}
		}

		void Restore()
		{
			isRestore = true;
		}
	}
}
