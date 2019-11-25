#pragma once

#include "../Communication/Interface.h"
#include "../Game/GameController.h"

namespace Communication
{
	// interfaces are bound to player. that causes
	// interface indexes to be the same as the player
	// ones
	namespace InterfaceManager
	{
		struct FID
		{
			enum
			{
				REMOVE_INVALID_PLAYERID = 2
			};
		};

		void RegisterFaultNotifier();

		void Initialize();
		void Unintialize();

		void Process(const bool update);

		void PushInterface(Interface* const interface);
		void LinkInterface(Interface* const interface, const int);

		template <typename InterfaceT>
		Interface* CreatePushedInterface()
		{
			Interface* const interface = new InterfaceT();
			PushInterface(interface);
			return interface;
		}

		template <typename InterfaceT>
		Interface* CreateLinkedInterface(const int playerIndex)
		{
			Interface* const interface = new InterfaceT();
			LinkInterface(interface, playerIndex);
			return interface;
		}

		void RemoveInterface(const Game::PlayerId);
		bool ExistsInterface(const Game::PlayerId);
	}
}
