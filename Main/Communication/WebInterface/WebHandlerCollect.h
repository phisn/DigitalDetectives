#pragma once

#include "../../Communication/InterfaceManager.h"

#include "../../Communication/WebInterface/WebServerManager.h"
#include "../../Communication/WebInterface/Website/WebsiteCollect.h"
#include "../../Communication/WebInterface/WebInterface.h"

#include "../../Game/GameController.h"

namespace
{
	using namespace Communication;

	void WritePlayerId(
		AsyncWebServerResponse* const response,
		const Game::PlayerId playerId)
	{
		char pidBuffer[4];
		itoa(playerId, pidBuffer, 10);
		pidBuffer[3] = '\0';

		response->addHeader(F("Set-Cookie"), pidBuffer);
	}
}

namespace Communication
{
	namespace WebHandler
	{
		void HandleCollectRequest(AsyncWebServerRequest* const request)
		{
			if (Game::Controller::GetState() != Game::GameState::Collect)
			{
				request->redirect(WEB_DIR_COMMON);
				return;
			}

			const Game::PlayerId playerId = WebServerManager::FindPlayerId(request);

			if (playerId == 0 && Game::Collector::GetData()->playerCount >= COMMON_MAX_PLAYERCOUNT)
			{
				request->redirect(WEB_DIR_REQPID);
				return;
			}

			AsyncWebServerResponse* const response = request->beginResponse_P(
				200,
				WEB_RESPONSE_TYPE,
				Website::Collect);

			if (playerId == 0)
			{
				WritePlayerId(
					response, 
					InterfaceManager::CreateInterface<WebInterfaceType>()->getPlayerId()
				);
			}

			request->send(response);
		}
	}
}
