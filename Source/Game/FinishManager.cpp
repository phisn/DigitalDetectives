#include "FinishManager.h"

namespace
{
	bool needsUpdate = true;
}

namespace Game
{
	namespace FinishManager
	{
		void Create()
		{
		}

		bool Process()
		{
			if (needsUpdate)
			{
				needsUpdate = false;
				return true;
			}

			return false;
		}

		void Restore()
		{
		}
	}
}