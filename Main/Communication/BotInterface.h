#pragma once

#include "../Communication/InterfaceManager.h"

namespace Communication
{
	class BotInterface
		:
		public Interface
	{
	public:
		void initialize(const Game::PlayerId playerId) override
		{
			this->playerId = playerId;
		}

		const Game::PlayerId getPlayerId() const override
		{
			return playerId;
		}

		bool process() override
		{
			if (Game::Controller::GetState() == Game::GameState::Running && 
				Game::GameManager::GetData()->state.activePlayer == playerId)
			{
				const Game::MapPosition position = Game::GameManager::ReadPlayer(playerId)->state->position;

				const Game::Station::Type type = (Game::Station::Type) random(
					(int) Game::PathManager::GetStationType(position).type
				);
				
				const Game::PathManager::FindOptionsSpecificResult options = Game::PathManager::FindOptionsSpecific(
					position,
					type
				);

				Game::Turn turn;

				turn.position = options.station[random(options.stationCount)];
				turn.ticket = (Game::Ticket) type;
				turn.doubleTicket = false;

				Game::GameManager::TurnResult result = Game::GameManager::MakeTurn(playerId, turn);
				if (result != Game::GameManager::TurnResult::Success)
				{
					Device::Fault fault;

					fault.id = 0xbb;
					fault.module = Device::FaultModule::InterfaceManager;
					fault.text = Game::GameManager::GetTurnFailReason(result);

					Device::FaultHandler::Handle(
						fault,
						true
					);
				}
			}

			return false;
		}

		void update() override
		{
		}

		void notifyFault(const Device::Fault fault) override
		{
		}

	private:
		Game::PlayerId playerId;
	};
}
