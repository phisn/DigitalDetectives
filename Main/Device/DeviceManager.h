#pragma once

#include <Device/MapManager.h>
#include <Device/NetworkManager.h>

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