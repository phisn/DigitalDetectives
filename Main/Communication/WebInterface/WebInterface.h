#pragma once

#include "../../Communication/InterfaceManager.h"
#include "../../Game/GameController.h"

#define COMM_WEBINT_WEBSOCK_TIMEOUT 500

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

		void process() override
		{
			// kick for timeout
			if (webSocketId == NULL)
			{
				webSocketTimeoutCounter = millis() - webSocketTimeoutLast;
				webSocketTimeoutLast = millis();

				if (webSocketTimeoutCounter > COMM_WEBINT_WEBSOCK_TIMEOUT)
				{
					Communication::InterfaceManager::RemoveInterface(playerId);

					return;
				}
			}
			else if (webSocketTimeoutCounter != 0)
			{
				webSocketTimeoutCounter = 0;
			}
		}

		void update() override
		{
		}

		WebsocketId getWebSocketId() const
		{
			return webSocketId;
		}

		const Game::PlayerId getPlayerId() const
		{
			return playerId;
		}

	private:
		WebsocketId webSocketId = 0;

		unsigned long webSocketTimeoutCounter = 0;
		unsigned long webSocketTimeoutLast = 0;

		Game::PlayerId playerId;
	};
}
