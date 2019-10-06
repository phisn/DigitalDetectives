#pragma once

#include "../Communication/Interface.h"
#include "../Game/GameController.h"

namespace Communication
{
	class SerialInterface
		:
		public Interface
	{
	public:
		void Process() override
		{
		}

		void Update() override
		{
			switch (sector->state)
			{
			case Game::GameState::Collect:
				UpdateCollect();

				break;
			case Game::GameState::Running:
				UpdateRunning();

				break;
			case Game::GameState::Setup:
				UpdateSetup();

				break;
			}
		}

	private:
		void UpdateCollect()
		{
			Serial.print("Collect update");

			Serial.write("-> playercount: ");
			Serial.print(sector->collect.playerCount);
		}

		void UpdateRunning()
		{
		}

		void UpdateSetup()
		{
		}

		const Game::GameSector* sector = Game::Controller::ReadSector();
	};
}
