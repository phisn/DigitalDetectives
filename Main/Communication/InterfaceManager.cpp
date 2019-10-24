#include "InterfaceManager.h"

#include "../Communication/SerialInterface.h"
#include "../Communication/WebInterface/WebInterface.h"

namespace
{
	// usage: InterfaceBuffer{ Communcation::xxxInterfaceType{} }
	union InterfaceBuffer
	{
		InterfaceBuffer(Communication::SerialInterfaceType)
			:
			active(Serial)
		{
			new (&serial) Communication::SerialInterface();
		}

		InterfaceBuffer(Communication::WebInterfaceType)
			:
			active(Web)
		{
			new (&web) Communication::WebInterface();
		}

		Communication::Interface* Get()
		{
			return (Communication::Interface*) this;
		}

		~InterfaceBuffer()
		{
			switch (active)
			{
			case Serial:
				serial.~SerialInterface();
	
				break;
			case Web:
				web.~WebInterface();
				
				break;
			}
		}

	private:
		const enum : unsigned char
		{
			Serial,
			Web

		} active;

		Communication::WebInterface web;
		Communication::SerialInterface serial;
	};

	char interfaces_buffer[sizeof(InterfaceBuffer) * COMMON_MAX_PLAYERCOUNT];
	InterfaceBuffer* interfaces = (InterfaceBuffer*) interfaces_buffer;

	FlashString fault_remove_invalid_playerid = DEVICE_FAULT_MESSAGE("Got invalid PlayerId in remove   ");
}

namespace Communication
{
	namespace InterfaceManager
	{
		void FaultNotifier(const Device::Fault fault);
		void CollectInterfaces();

		void Pop(Interface* const interface);
		void Push(Interface* const interface);

		void RegisterFaultNotifier()
		{
			Device::FaultHandler::RegisterFaultInterfaceNotifier(
				(Device::FaultHandler::InterfaceNotifierCallback) FaultNotifier
			);
		}

		void FaultNotifier(const Device::Fault fault)
		{
			if (Game::Controller::GetState() == Game::GameState::PreRunning)
			{
				return;
			}

			for (int i = 0; i < Game::Collector::GetData()->playerCount; ++i)
			{
				interfaces[i].Get()->notifyFault(fault);
			}
		}

		void Initialize()
		{
		}

		void Unintialize()
		{
		}

		void Process(const bool update)
		{
			if (Game::Controller::GetState() == Game::GameState::Collect)
			{
				CollectInterfaces();
			}

			for (int i = 0; i < Game::Collector::GetData()->playerCount; ++i)
			{
				Interface* const interface = interfaces[i].Get();

				if (update)
				{
					interface->update();
				}

				if (interface->process())
				{
					break;
				}
			}
		}

		// not all interfaces are collectable 
		// ex. webinterface because async
		void CollectInterfaces()
		{
			Communication::SerialInterface::UpdateCollect();
		}

		template <>
		Interface* CreateInterface<SerialInterfaceType>()
		{
			Interface* const interface = (new (
				&interfaces[
					Game::Collector::GetData()->playerCount
				]) InterfaceBuffer(Communication::SerialInterfaceType{})
			)->Get();

			Push(interface);

			return interface;
		}

		template <>
		Interface* CreateInterface<WebInterfaceType>()
		{
			Interface* const interface = (new (
				&interfaces[
					Game::Collector::GetData()->playerCount
				]) InterfaceBuffer(Communication::WebInterfaceType{})
			)->Get();

			Push(interface);

			return interface;
		}

		void RemoveInterface(const Game::PlayerId playerId)
		{
			for (int i = 0; i < Game::Collector::GetData()->playerCount; ++i)
				if (interfaces[i].Get()->getPlayerId() == playerId)
				{
					if (!Game::Collector::RemovePlayer(playerId))
					{
						break; // throw common removeinterface failure
					}

					interfaces[i].~InterfaceBuffer();

					// playercount is already one smaller from RemovePlayer
					for (int j = i; j < Game::Collector::GetData()->playerCount; ++j)
					{
						memcpy(&interfaces[j], &interfaces[j + 1], sizeof(InterfaceBuffer));
					}

					return;
				}
			
#ifdef VM_DEBUG
			DEBUG_MESSAGE("GOT");
			DEBUG_MESSAGE(playerId);
			DEBUG_MESSAGE("HAVE");

			for (int i = 0; i < Game::Collector::GetData()->playerCount; ++i)
				DEBUG_MESSAGE(interfaces[i].Get()->getPlayerId());

			DEBUG_MESSAGE("END HAVE");

#endif

			Device::FaultHandler::Handle(
				{
					Device::FaultModule::InterfaceManager,
					InterfaceManager::FID::REMOVE_INVALID_PLAYERID,
					fault_remove_invalid_playerid
				}, true);
		}

		void Push(Interface* const interface)
		{
			interface->initialize(
				Game::Collector::CreatePlayer()
			);
		}

		void Pop(Interface * const interface)
		{
		}
	}
}
