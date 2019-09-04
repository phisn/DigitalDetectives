#pragma once

#include "../Device/FaultHandler.h"

namespace Device
{
	struct BootSector
	{
		enum State : unsigned char
		{
			Shutdown,

			Collect,
			Setup,
			Running,

			RestoreRunning_Collect, // currently restoring a old running state (collecting players)
			RestoreRunning_Game // currently restoring a old running state (restoring game internals)

		} state;
	};

	namespace BootManager
	{
		void Initialize();
		void Uninitialize();

		void Boot(); // called single time at begin by devicemanager
		void Process(); // called on module finish (forward by devicemanager)

		BootSector* _GetCurrentBootSector();
	}
}
