#pragma once

#include <Communication/InterfaceManager.h>
#include <Communication/RequestHandler.h>

#include <Device/MapManager.h>
#include <Device/NetworkManager.h>

#include <Game/GameAccess.h>

namespace Device::Manager
{
	enum class State
	{
		Collect,
		Setup,
		Running

	};

	void Initialize();
	void Uninitialize();

	void Process();

	State GetCurrentState();
	void SetCurrentState(const State);
}