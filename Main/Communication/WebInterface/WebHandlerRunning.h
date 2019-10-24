#pragma once

#include "../../Communication/InterfaceManager.h"

#include "../../Communication/WebInterface/WebServerManager.h"
#include "../../Communication/WebInterface/WebInterface.h"

#include "../../Game/GameController.h"

namespace
{
	using namespace Communication;
}

namespace Communication
{
	namespace Website
	{
		const char* Running PROGMEM =
R"(
)";
	}

	namespace WebHandler
	{
		void HandleCollectRequest(AsyncWebServerRequest* const request)
		{
			if (Game::Controller::GetState() != Game::GameState::Running)
			{
				request->redirect(WEB_DIR_COMMON);
				return;
			}

			const Game::PlayerId playerId = WebServerManager::EnforcePlayerId(request);

			if (playerId == 0)
			{
				return;
			}

			request->send_P(
				200,
				WEB_RESPONSE_TYPE,
				Website::Running);
		}
	}
}
