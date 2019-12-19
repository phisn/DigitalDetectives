#pragma once

#include "../Device/OutputManager.h"
#include "../Device/MapManager.h"

#include "../Game/Data/GameSector.h"

// speed of moving characters
#define GAME_BOARDMANAGER_COLLECT_LCDSPEED 500

// REP speed is the time a flashing led needs to do a full circle
// normal speed is the time a led needs for a tick / color change
#define GAME_BOARDMANAGER_RUNNING_LEDSPEED_REP 1440
#define GAME_BOARDMANAGER_RUNNING_LEDSPEED 120

namespace Game
{
	namespace BoardManager
	{
		void Process();
		void Update();

		// indicate last element
		// by NULL as position
		struct AnimationElement
		{
			MapPosition position;
			CRGB color;
			unsigned long time;
		};

		enum class AnimationSpeciality
		{
			Normal,
			Running // show villian
		};

		void RunAnimation(AnimationElement* const animation, 
			AnimationSpeciality speciality = AnimationSpeciality::Normal);
		bool IsAnimationRunning();

		void OnStateChanged(const Game::GameState newState);
		void ReloadLcd();
	}
}
