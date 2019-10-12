#include "InterfaceManager.h"

#include "../Communication/SerialInterface.h"
#include "../Communication/WebInterface.h"

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

	InterfaceBuffer interfaces[GAME_MAX_PLAYERCOUNT];

	FlashString fault_remove_invalid_playerid = DEVICE_FAULT_MESSAGE("Got invalid PlayerId in remove");
}

namespace Communication
{
	void ProcessInterfaces();

	void Pop(Interface* const interface);
	void Push(Interface* const interface);

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

	template <>
	void InterfaceManager::CreateInterface<SerialInterfaceType>()
	{
		Push(new (
			&interfaces[
				Game::Collector::GetData()->playerCount
			]) InterfaceBuffer(Communication::SerialInterfaceType{}
		)->Get());
	}

	template <>
	void InterfaceManager::CreateInterface<WebInterfaceType>()
	{
		Push(new (
			&interfaces[
				Game::Collector::GetData()->playerCount
			]) InterfaceBuffer(Communication::WebInterfaceType{}
		)->Get());
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

				for (int j = i; j < Game::Collector::GetData()->playerCount - 1; ++j)
				{
					memcpy(&interfaces[j], &interfaces[j + 1], sizeof(InterfaceBuffer));
				}

				return;
			}

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

	void Pop(Interface* const interface)
	{
	}
}
