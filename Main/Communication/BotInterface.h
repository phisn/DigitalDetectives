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
				unsigned char path[6][8][200];

				for (int i = 0; i < 6; ++i)
				{
					path[i][0][Game::GameManager::GetData()->player[i].position] = 1;
				}

				for (int turns = 1; turns < 8; ++turns)
				{
					for (int players = 0; players < 6; ++players)
					{
						for (int reachable = 0; reachable < 200; ++reachable)
						{
							if (path[players][turns - 1][reachable])
							{
								for (int l = 0; l < 4; ++l)
								{
									const Game::PathManager::FindOptionsSpecificResult options = Game::PathManager::FindOptionsSpecific(
										path[players][turns - 1][reachable],
										(Game::Station::Type) l
									);

									for (int m = 0; m < options.stationCount; ++m)
									{
										path[players][turns][options.station[m]] = 1;
									}
								}
							}
						}
					}

					// mrx
					for (int i = 0; i < 200; i++) {
						for (int players = 1; players < 6; ++players)
						{
							if (path[players][turns][i]) {
								path[0][turns][i] = 0;
								break;
							}
						}
					}

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
