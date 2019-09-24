#include "DeviceManager.h"

#include "../Communication/InterfaceManager.h"
#include "../Communication/RequestHandler.h"

#include "../Device/Logger.h"
#include "../Device/MapManager.h"
#include "../Device/NetworkManager.h"

#include "../Game/GameController.h"

namespace
{
	Device::Manager::State currentState;
}

namespace Device
{
	namespace Manager
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
		void InitializeGame();
		void InitializeCommunication();

		void Initialize()
		{
			InitializeDevice();
			InitializeGame();
			InitializeCommunication();

			// old
			// currentState = State::Collect;

			// BootManager::Boot();
		}

		void Uninitialize()
		{
		}

		void InitializeDevice()
		{
			DEBUG_MESSAGE("Device Init (low)");

			StatusLED::Initialize();

			FailureHandler::Initialize();
			MemoryManager::Initialize();
			OutputManager::Initialize();

			DEBUG_MESSAGE("Device Init (high)");

			FaultHandler::Initialize();
			MapManager::Initialize();
			NetworkManager::Initialize();

			DEBUG_MESSAGE("Device Init finished");
		}

		void InitializeGame()
		{
			Game::Controller::Initialize();
		}

		void InitializeCommunication()
		{
			Communication::InterfaceManager::Initialize();
			Communication::RequestHandler::Initialize();
		}

		void Process()
		{
			/*
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
			*/

			FaultHandler::ValidateDeviceState();
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
}
