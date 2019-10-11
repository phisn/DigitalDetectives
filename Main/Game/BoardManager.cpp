#include "BoardManager.h"
#include "../Game/GameController.h"

namespace
{
	// change read later (dependencies)
	const Game::GameSector* sector = Game::Controller::ReadSector();

	FlashString cmessage_common_0 = DEVICE_LCD_MESSAGE("Waiting for players ");
	FlashString cmessage_common_1_part = FPSTR("Currently: ");
}

namespace Game
{
	namespace BoardManager
	{
		void UpdateCollect();
		void UpdateRunning();
		void UpdateSetup();

		void Update()
		{
			switch (sector->state)
			{
			case GameState::Collect:
				UpdateCollect();

				break;
			case GameState::Running:
				UpdateRunning();

				break;
			case GameState::Setup:
				UpdateSetup();

				break;
			}
		}

		void UpdateCollect()
		{
			Device::OutputManager::Lcd::Clear();
			Device::OutputManager::Lcd::DisplayLineType(
				0,
				cmessage_common_0
			);

			char lcdBuffer[DEVICE_LCD_WIDTH];

			sprintf_P(
				lcdBuffer, PSTR("%s: %d"),
				cmessage_common_1_part,
				sector->collect.playerCount
			);

			Device::OutputManager::Lcd::DisplayLineType(
				1,
				lcdBuffer
			);
		}

		void UpdateRunning()
		{
		}

		void UpdateSetup()
		{
		}
	}
}
