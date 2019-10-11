#pragma once

#include "../Communication/Interface.h"
#include "../Game/GameController.h"

namespace Communication
{
	namespace InterfaceManager
	{
		struct FID
		{
			enum
			{
				REMOVE_INVALID_PLAYERID = 2
			};
		};

		void Initialize();
		void Unintialize();

		void Process();

		template <typename InterfaceType>
		void CreateInterface();
		void RemoveInterface(const Game::PlayerId);
	}
}
