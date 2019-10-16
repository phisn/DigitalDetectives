#pragma once

#include "../Communication/Interface.h"
#include "../Game/GameController.h"

namespace Communication
{
	struct WebInterfaceType {};
	class WebInterface
		:
		public Interface
	{
	public:
		static void Collect()
		{
		}

		void initialize(const Game::PlayerId id) override
		{
			playerId = id;
		}

		void notifyFault(const Device::Fault fault) override
		{
		}

		void process() override
		{
		}

		void update() override
		{
		}

		const Game::PlayerId getPlayerId() const
		{
			return playerId;
		}

	private:
		Game::PlayerId playerId;
	};
}
