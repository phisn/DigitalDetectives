#include "WebInterface.h"
#include "../../Communication/WebInterface/WebServerManager.h"

namespace Communication
{
	WebInterface::~WebInterface()
	{

	}

	void WebInterface::initialize(const Game::PlayerId id)
	{
		playerId = id;
		unregisterWebSocket();
	}
}
