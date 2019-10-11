#pragma once

#include "../Communication/Interface.h"
#include "../Game/GameController.h"

namespace Communication
{
	struct SerialInterfaceType {};
	class SerialInterface
		:
		public Interface
	{
	public:
		void initialize(const Game::PlayerId id) override
		{
			playerId = id;
		}

		void process() override
		{
		}

		void update() override
		{
			switch (Game::Controller::GetState())
			{
			case Game::GameState::Collect:
				updateCollect();

				break;
			case Game::GameState::Running:
				updateRunning();

				break;
			case Game::GameState::Setup:
				updateSetup();

				break;
			}
		}

		const Game::PlayerId getPlayerId() const
		{
			return playerId;
		}

	private:
		Game::PlayerId playerId;

		void updateCollect()
		{
			Serial.print("Collect update");

			Serial.write("-> playercount: ");
			Serial.print(Game::Collector::GetData()->playerCount);
		}

		void updateRunning()
		{
		}

		void updateSetup()
		{
		}
	};
}
