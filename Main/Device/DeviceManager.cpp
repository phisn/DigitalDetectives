#include "DeviceManager.h"

#include "../Communication/InterfaceManager.h"
#include "../Communication/RequestHandler.h"

#include "../Device/BootManager.h"
#include "../Device/MapManager.h"
#include "../Device/NetworkManager.h"

#include "../Game/GameAccess.h"

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
		void InitilaizeGame();
		void InitializeCommunication();

		void Initialize()
		{
			InitializeDevice();
			InitilaizeGame();
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
			Game::Access::Initialize();
		}

		void InitializeCommunication()
		{
			Communication::InterfaceManager::Initialize();
			Communication::RequestHandler::Initialize();
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

		void Exit()
		{
			BootManager::Process(); // forward
		}
	}
}
