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
			DEBUG_MESSAGE("Update");

			if (webSocketId == 0)
			{
				DEBUG_MESSAGE("Fail 0");
				return;
			}

			const Game::GameState currentState = Game::Controller::GetState();
			if (lastState != currentState)
			{
				DEBUG_MESSAGE("Update, change state");

				lastState = currentState;

				WebSocketData::RedirectData data;
				sendData((const char*) &data, sizeof(data));
			}

			switch (lastState)
			{
			case Game::GameState::Collect:
			{
				DEBUG_MESSAGE("State collect");

				WebSocketData::CollectData data;
				data.playerCount = Game::Collector::GetData()->playerCount;
				sendData((const char*) &data, sizeof(data));
			}
				break;
			case Game::GameState::Running:
			{
				DEBUG_MESSAGE("State running");

				const Game::Player* const player = Game::GameManager::ReadPlayer(playerId);

				if (player == NULL)
				{
					DEBUG_MESSAGE("Got empty player (players)");

#ifdef VM_DEBUG
					for (int i = 0; i < Game::Collector::GetData()->playerCount; ++i)
					{
						DEBUG_MESSAGE(Game::SetupManager::GetData()->playerContext.data[i].player);
					}
#endif

					DEBUG_MESSAGE("Searching: ");
					DEBUG_MESSAGE(playerId);

					break;
				}

				WebSocketData::RunningData data;

				data.playerCount = Game::Collector::GetData()->playerCount;
				data.currentPlayer = Game::GameManager::GetData()->state.activePlayer;

				data.playerType = player->data->type;
				data.position = player->state->position;

				data.yellowTicketCount = player->state->ticket.yellowTicketCount;
				data.greenTicketCount = player->state->ticket.greenTicketCount;
				data.redTicketCount = player->state->ticket.redTicketCount;

				data.positionVillianReveal = Game::GameManager::GetShowVillianPositionRound();

				if (data.playerType == Game::PlayerData::Type::Villian)
				{
					data.villian.blackTicketCount = player->state->villian.ticket.blackTicketCount;
					data.villian.doubleTicketCount = player->state->villian.ticket.doubleTicketCount;

					// skip villian
					for (int i = 1; i < Game::Collector::GetData()->playerCount; ++i)
					{
						const Game::Player* const detPlayer = Game::GameManager::ReadPlayerByIndex(i);
						
						data.villian.detYellowTickets[i - 1] = detPlayer->state->ticket.yellowTicketCount;
						data.villian.detGreenTickets[i - 1] = detPlayer->state->ticket.greenTicketCount;
						data.villian.detRedTickets[i - 1] = detPlayer->state->ticket.redTicketCount;
					}

					const Game::PathManager::FindOptionsSpecificResult result = Game::PathManager::FindOptionsSpecific(
						player->state->position,
						Game::Station::Ferry);

					data.villian.turnFerryCount = result.stationCount;

					// unrolled
					data.villian.turnFerry[0] = result.station[0];
					data.villian.turnFerry[1] = result.station[1];
				}
				else
				{
					data.detective.positionVillian = Game::GameManager::GetLastVillianPosition();

					// villian index is always 0
					const Game::Player* const villian = Game::GameManager::ReadPlayerByIndex(0);

					data.detective.villianYellowTicketCount = villian->state->ticket.yellowTicketCount;
					data.detective.villianGreenTicketCount = villian->state->ticket.greenTicketCount;
					data.detective.villianRedTicketCount = villian->state->ticket.redTicketCount;

					data.detective.villianBlackTicketCount = villian->state->villian.ticket.blackTicketCount;
					data.detective.villianDoubleTicketCount = villian->state->villian.ticket.doubleTicketCount;

					data.detective.color = player->data->color;
				}

				const Game::PathManager::FindOptionsSpecificResult 
					taxiResult = Game::PathManager::FindOptionsSpecific(
						player->state->position,
						Game::Station::Taxi),
					busResult = Game::PathManager::FindOptionsSpecific(
						player->state->position,
						Game::Station::Bus),
					undergroundResult = Game::PathManager::FindOptionsSpecific(
						player->state->position,
						Game::Station::Underground);

				data.turnYellowCount = taxiResult.stationCount;
				data.turnGreenCount = busResult.stationCount;
				data.turnRedCount = undergroundResult.stationCount;

				memcpy(data.turnYellow, taxiResult.station, taxiResult.stationCount);
				memcpy(data.turnGreen, busResult.station, busResult.stationCount);
				memcpy(data.turnRed, undergroundResult.station, undergroundResult.stationCount);

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

		Game::GameState lastState;
		Game::PlayerId playerId;
	};
}
