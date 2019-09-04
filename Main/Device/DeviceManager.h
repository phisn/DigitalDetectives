#pragma once

namespace Device
{
	namespace Manager
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
		void Exit();

		State GetCurrentState();
		void SetCurrentState(const State);
	}
}