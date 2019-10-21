#pragma once

#include "../../Communication/WebInterface/WebInterface.h"
#include "../../Game/GameController.h"

#define WEB_DIR_COMMON F("/")
#define WEB_DIR_COLLECT F("/collect")
#define WEB_DIR_REQPID F("/requestpid")

#define WEB_PARAM_PLAYERID F("playerid")

#define WEB_RESPONSE_TYPE F("text/html")

#define WEB_MAX_CONN 10

namespace Communication
{
	typedef uint32_t WebsocketId;

	struct WebCode
	{
		enum
		{
			_Begin = 2,

			WebSocketInvalidPid
		};
	}

	namespace WebServerManager
	{
		void Initialize();

		Game::PlayerId FindPlayerId(AsyncWebServerRequest* const request);
		Game::PlayerId EnforcePlayerId(AsyncWebServerRequest* const request);

		void RegisterWebInterface(WebInterface* const interface);
		void UnregisterWebInterface(WebInterface* const interface);
	}
}
