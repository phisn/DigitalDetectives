#pragma once

#include "../Communication/Interface.h"
#include "../Game/GameController.h"

namespace Communication
{
	namespace InterfaceManager
	{
		void Initialize();
		void Unintialize();

		void Process();
	}
}
