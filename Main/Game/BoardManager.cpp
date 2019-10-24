#include "BoardManager.h"
#include "../Game/Data/GameSector.h"

namespace
{
	struct
	{
		union
		{
			struct
			{
				unsigned long nextUpdate;
				char flowingText[DEVICE_LCD_WIDTH * 2];

			} collect;

			struct
			{
			} setup;

			struct
			{
			} running;
		};

		unsigned long lastTime = millis();
		unsigned long timer = millis();

	} dynamicStateData;

	FlashString message_collect_0 = DEVICE_LCD_MESSAGE("Waiting for players ");
	FlashString message_collect_1 = FPSTR("Currently: %d");

	FlashString message_running_0 = DEVICE_LCD_MESSAGE("  - Running game -  ");
	FlashString message_running_1 = FPSTR("Current round: %d");
	FlashString message_running_2 = FPSTR("Current player: %x");
}

namespace Game
{
	namespace BoardManager
	{
		void UpdateCollect();
		void UpdateRunning();
		void UpdateSetup();

		void Process()
		{
			const unsigned long time = millis();
			dynamicStateData.timer += time - dynamicStateData.lastTime;
			dynamicStateData.lastTime = time;

			switch (Controller::GetState())
			{
			case GameState::Collect:
				if (dynamicStateData.timer > dynamicStateData.collect.nextUpdate)
				{
					for (int i = DEVICE_LCD_WIDTH * 2 - 1; i > 0; --i)
					{
						if (i >= DEVICE_LCD_WIDTH)
						{
							const int source = i == DEVICE_LCD_WIDTH
								? i - 1
								: 20 + 40 - i;

							const int target = 20 + 39 - i;

							dynamicStateData.collect.flowingText[target] = dynamicStateData.collect.flowingText[source];
						}
						else
						{
							dynamicStateData.collect.flowingText[i] = dynamicStateData.collect.flowingText[i - 1];
						}
					}

					dynamicStateData.collect.flowingText[0] = (random(0xffff) % 2 == 0) ? '+' : '-';

					Device::OutputManager::Lcd::DisplayLineType(
						2,
						dynamicStateData.collect.flowingText,
						DEVICE_LCD_WIDTH);
					Device::OutputManager::Lcd::DisplayLineType(
						3,
						dynamicStateData.collect.flowingText + DEVICE_LCD_WIDTH,
						DEVICE_LCD_WIDTH);

					dynamicStateData.collect.nextUpdate = dynamicStateData.timer + 500;
				}

				break;
			}
		}

		void Update()
		{
			switch (Controller::GetState())
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
				message_collect_0
			);

			char lcdBuffer[DEVICE_LCD_WIDTH];

			sprintf_P(
				lcdBuffer, 
				(char*) message_collect_1,
				Collector::GetData()->playerCount
			);

			Device::OutputManager::Lcd::DisplayLineType(
				1,
				lcdBuffer
			);
		}

		void UpdateRunning()
		{
			Device::OutputManager::FastLed::Clear();

			// skip villian (= 0)
			for (int i = 1; i < Collector::GetData()->playerCount; ++i)
			{
				Device::OutputManager::FastLed::Show(
					Device::MapManager::Translate(
						GameManager::GetData()->player[i].position
					),
					ColorToCRGB(SetupManager::GetData()->playerContext.data[i].color)
				);
			}

			// villian is shown as white
			if (GameManager::IsShowVillianPositionRound())
			{
				Device::OutputManager::FastLed::Show(
					Device::MapManager::Translate(
						GameManager::GetData()->player[0].position
					),
					CRGB::White);
			}

			Device::OutputManager::FastLed::Update();

			Device::OutputManager::Lcd::Clear();
			Device::OutputManager::Lcd::DisplayLineType(
				0,
				message_running_0
			);

			char lcdBuffer[DEVICE_LCD_WIDTH];

			sprintf_P(
				lcdBuffer,
				(char*) message_running_1,
				Game::GameManager::GetData()->state.round + 1
			);

			Device::OutputManager::Lcd::DisplayLineType(
				1,
				lcdBuffer
			);

			sprintf_P(
				lcdBuffer,
				(char*) message_running_2,
				Game::GameManager::GetData()->state.activePlayer
			);

			Device::OutputManager::Lcd::DisplayLineType(
				2,
				lcdBuffer
			);
		}

		void UpdateSetup()
		{
		}

		void OnStateChanged(const Game::GameState newState)
		{
			DEBUG_MESSAGE("Boardmanager state changed");

			switch (newState)
			{
			case GameState::Collect:
				dynamicStateData.collect.nextUpdate = 0;
				memset(
					&dynamicStateData.collect.flowingText, 
					' ', 
					sizeof(dynamicStateData.collect.flowingText));
				
				break;
			default:
				memset(&dynamicStateData, 0, sizeof(dynamicStateData));

				break;
			}
		}
	}
}
