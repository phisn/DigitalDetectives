#include "WebServerManager.h"

#include "../../Communication/WebInterface/WebHandlerCollect.h"

namespace
{
	WebInterface* interfaces[COMMON_MAX_PLAYERCOUNT] = { };
}

namespace Communication
{
	namespace WebServerManager
	{
		AsyncWebServer* _GetServer()
		{
			static AsyncWebServer* const server = new AsyncWebServer(80);
			return server;
		}

		AsyncWebSocket* _GetSocket()
		{
			static AsyncWebSocket* const socket = new AsyncWebSocket("/ws");
			return socket;
		}

		void HandleCommonRequest(AsyncWebServerRequest* const request);
		
		void HandleWebSocketEvent(
			AsyncWebSocket* const socket,
			AsyncWebSocketClient* const client,
			const AwsEventType type,
			void* const arg,
			uint8_t* const data,
			const size_t length);

		void Initialize()
		{
			AsyncWebServer* const server = _GetServer();
			AsyncWebSocket* const socket = _GetSocket();

			server->on(WEB_DIR_COMMON, HTTP_GET, HandleCommonRequest);
			server->on(WEB_DIR_COLLECT, HTTP_GET, WebHandler::HandleCollectRequest);

			server->onNotFound([](AsyncWebServerRequest* const request) 
			{
				request->redirect(WEB_DIR_COMMON);
			});

			socket->onEvent(HandleWebSocketEvent);

			server->begin();
		}

		void HandleCommonRequest(AsyncWebServerRequest* const request)
		{
			switch (Game::Controller::GetState())
			{
			case Game::GameState::Collect:
				request->redirect(WEB_DIR_COMMON);

				break;
			}
		}

		Game::PlayerId EnforcePlayerId(AsyncWebServerRequest* const request)
		{
			const Game::PlayerId playerId = FindPlayerId(request);

			if (playerId == 0)
			{
				request->redirect(WEB_DIR_REQPID);
			}

			return playerId;
		}

		Game::PlayerId FindPlayerId(AsyncWebServerRequest* const request)
		{
			// read and validate
			AsyncWebHeader* const cookieHeader = request->getHeader(F("Cookie"));

			if (cookieHeader != nullptr) // nullptr on fail
			{
				const Game::PlayerId pid = cookieHeader->value().toInt();

				for (int i = 0; i < Game::Collector::GetData()->playerCount; ++i)
					if (Game::Collector::GetData()->playerIds[i] == pid)
					{
						return pid;
					}
			}

			return 0;
		}

		void HandleWebSocketEvent(
			AsyncWebSocket* const socket,
			AsyncWebSocketClient* const client,
			const AwsEventType type,
			void* const arg,
			uint8_t* const data,
			const size_t length)
		{
			switch (type)
			{
			case WS_EVT_CONNECT:
				// arg: request (AsyncWebServerRequest*)
				// data: NULL
				// length: 0

				const Game::PlayerId pid = FindPlayerId((AsyncWebServerRequest*) arg);

				if (pid == 0)
				{
					client->close(WebCode::WebSocketInvalidPid);
				}
				else
				{
					for (int i = 0; i < COMMON_MAX_PLAYERCOUNT; ++i)
						if (interfaces[i] && interfaces[i]->getPlayerId() == pid)
						{
							interfaces[i]->registerWebSocket(client->id());

							break;
						}
				}

				break;
			case WS_EVT_DISCONNECT:
				// arg: NULL
				// data: NULL
				// length: 0

				for (int i = 0; i < COMMON_MAX_PLAYERCOUNT; ++i)
					if (interfaces[i] && interfaces[i]->getWebSocketId() == client->id())
					{
						interfaces[i]->unregisterWebSocket();
					}

				break;
			case WS_EVT_ERROR:
				// arg: reasoncode (uint16_t)
				// data: reasonString (char*)
				// length: datalen

				// TODO: thinking about showing reasoncode 
				// and reasonstring in faultmanager fault

				break;
			case WS_EVT_DATA:
				// arg: _pinfo (AwsFrameInfo*)
				// data: data (uint8_t*)
				// length: datalen

				// no data will be ever sent from
				// a client!

				break;
			case WS_EVT_PONG:
				// arg: NULL
				// data: data (uint8_t*)
				// length: datalen

				// reserved for later use. maybe to
				// ensure connection to a user, but
				// with current webinterface system
				// there is no need for this (websocks
				// are always bound to webinterfaces
				// and webints do kick inactive 
				// websockets)

				break;
			}
		}

		void RegisterWebInterface(WebInterface* const interface)
		{
			for (int i = 0; i < COMMON_MAX_PLAYERCOUNT; ++i)
				if (interfaces[i] == NULL)
				{
					interfaces[i] = interface;
				}
		}

		void UnregisterWebInterface(WebInterface* const interface)
		{
			for (int i = 0; i < COMMON_MAX_PLAYERCOUNT; ++i)
				if (interfaces[i] == interface)
				{
					interfaces[i] = NULL;
				}
		}
	}
}
