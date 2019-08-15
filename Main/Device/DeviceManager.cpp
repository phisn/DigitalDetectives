#include "DeviceManager.h"

namespace
{
	Device::Manager::State currentState;
}

namespace Device::Manager
{
	State GetCurrentState()
	{
		return currentState;
	}

	void SetCurrentState(const State state)
	{
		currentState = state;
	}

	void ProcessCollect();
	void ProcessSetup();
	void ProcessRunning();

	void InitializeDevice();
	void InitilaizeGame();
	void InitializeCommunication();

	void Initialize()
	{
		InitializeDevice();
		InitilaizeGame();
		InitializeCommunication();

		currentState = State::Collect;
	}

	void Uninitialize()
	{
	}

	void InitializeDevice()
	{
		StatusLED::Initialize();

		FailureHandler::Initialize();
		MemoryManager::Initialize();
		OutputManager::Initialize();
		FaultHandler::Initialize();
		MapManager::Initialize();
		NetworkManager::Initialize();
	}

	void InitilaizeGame()
	{
	}

	void InitializeCommunication()
	{
	}

	void Process()
	{
		switch (currentState)
		{
		case State::Collect:
			ProcessCollect();

			break;
		case State::Setup:
			ProcessSetup();

			break;
		case State::Running:
			ProcessRunning();

			break;
		}
	}

	void ProcessCollect()
	{

	}

	void ProcessSetup()
	{

	}

	void ProcessRunning()
	{

	}
}
