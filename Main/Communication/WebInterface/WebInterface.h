#pragma once

#include "../../Communication/InterfaceManager.h"
#include "../../Communication/WebInterface/WebSocketData.h"

#include "../../Game/GameController.h"

#define COMM_WEBINT_WEBSOCK_TIMEOUT 2000

namespace Communication
{
	struct WebInterfaceType {};
	class WebInterface
		:
		public Interface
	{
	public:
		~WebInterface();
		void initialize(const Game::PlayerId id) override;

		void registerWebSocket(const uint32_t id)
		{
			DEBUG_MESSAGE("Register Socket");
			webSocketId = id;
		}

		void unregisterWebSocket()
		{
			webSocketId = NULL;

			webSocketTimeoutCounter = 0;
			webSocketTimeoutLast = millis();
		}

		void notifyFault(const Device::Fault fault) override
		{
		}

		bool process() override
		{
			// kick for timeout
			if (webSocketId == NULL)
			{
				DEBUG_MESSAGE("NO WEBSOCKET ID");
				DEBUG_MESSAGE(webSocketTimeoutCounter);

				webSocketTimeoutCounter += millis() - webSocketTimeoutLast;
				webSocketTimeoutLast = millis();

				if (webSocketTimeoutCounter > COMM_WEBINT_WEBSOCK_TIMEOUT)
				{
					Communication::InterfaceManager::RemoveInterface(playerId);
					return true;
				}
			}
			else if (webSocketTimeoutCounter != 0)
			{
				webSocketTimeoutCounter = 0;
			}

			return false;
		}

		void update() override
		{
			if (webSocketId == 0)
			{
				return;
			}

			switch (Game::Controller::GetState())
			{
			case Game::GameState::Collect:
			{
				WebSocketData::CollectData data;
				data.playerCount = Game::Collector::GetData()->playerCount;
				sendData((const char*) &data, sizeof(data));
			}
				break;
			}
		}

		uint32_t getWebSocketId() const
		{
			return webSocketId;
		}

		const Game::PlayerId getPlayerId() const
		{
			return playerId;
		}

	private:
		void sendData(const char* const data, const int length);

		uint32_t webSocketId = 0;

		unsigned long webSocketTimeoutCounter = 0;
		unsigned long webSocketTimeoutLast = 0;

		Game::PlayerId playerId;
	};
}
