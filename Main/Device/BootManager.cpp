#include "BootManager.h"

namespace
{
	Device::BootSector* bootSector;
}

namespace Device
{
	void BootManager::Initialize()
	{
		bootSector = Device::BootManager::_GetCurrentBootSector();
	}

	void BootManager::Uninitialize()
	{
	}

	void StartSession();
	void RestoreSession();

	void BootManager::Boot()
	{
		MemoryManager::ReadSector(
			MemorySector::Boot,
			(char*) bootSector
		);

		switch (bootSector->state)
		{
		case BootSector::Running:
			RestoreSession();

			break;
		default:
			// report possible error
			// if state is not common
			if (bootSector->state != BootSector::Shutdown)
			{
				FaultHandler::Report();
			}

			StartSession();

			break;
		}
	}

	void StartSession()
	{
		bootSector->state = BootSector::Collect;
	}

	void RestoreSession()
	{
		bootSector->state = BootSector::RestoreRunning_Collect;
	}

	void ProcessCollect();
	void ProcessSetup();
	void ProcessRestoreCollect();
	void ProcessRunning();

	void BootManager::Process()
	{
		switch (bootSector->state)
		{
		case BootSector::Collect: // -> Setup
			break;
		case BootSector::Setup: // -> Running (start)
			break;
		case BootSector::RestoreRunning_Collect: // -> Running (restore)
			break;
		case BootSector::Running: // -> restart | new phase like Ending
			break;
		}
	}

	void ProcessCollect()
	{
	}

	void ProcessSetup()
	{
	}

	void ProcessRestoreCollect()
	{
	}

	void ProcessRunning()
	{
	}

	BootSector* BootManager::_GetCurrentBootSector()
	{
		static BootSector bootSector;
		return &bootSector;
	}
}
