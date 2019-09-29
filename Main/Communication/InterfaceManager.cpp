#include "InterfaceManager.h"

namespace Communication
{
	void ProcessInterfaces();

	void InterfaceManager::Initialize()
	{
	}

	void InterfaceManager::Unintialize()
	{
	}

	void InterfaceManager::Process()
	{
		Game::Controller::Process();
		ProcessInterfaces();
	}

	void ProcessInterfaces()
	{
	}
}
