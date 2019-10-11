#pragma once

#include "../Game/Collector.h"

namespace Communication
{
	struct Interface
	{
		virtual void initialize(const Game::PlayerId id) = 0;

		virtual void process() = 0;
		virtual void update() = 0;

		virtual const Game::PlayerId getPlayerId() const = 0;
	};
}
