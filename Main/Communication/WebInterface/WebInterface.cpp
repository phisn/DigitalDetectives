#include "WebInterface.h"
#include "../../Communication/WebInterface/WebServerManager.h"

namespace Communication
{
	WebInterface::~WebInterface()
	{
		WebServerManager::UnregisterWebInterface(this);
	}

	void WebInterface::initialize(const Game::PlayerId id)
	{
		playerId = id;
		unregisterWebSocket();

		WebServerManager::RegisterWebInterface(this);
	}

	void WebInterface::sendData(
		const char* const data,
		const int length)
	{
		WebServerManager::SendWebSocketData(webSocketId, data, length);
	}
}
