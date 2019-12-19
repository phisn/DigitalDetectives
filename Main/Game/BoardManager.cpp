#include "BoardManager.h"
#include "../Game/Data/GameSector.h"
#include "../Game/GameManager.h"

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
				struct
				{
					unsigned long nextUpdate;
					uint16_t powerCounter;

				} led;

			} running;
		};

		unsigned long lastTime = millis();
		unsigned long timer = millis();

	} dynamicStateData;

	namespace Animation
	{
		unsigned long nextUpdate;
		Game::BoardManager::AnimationSpeciality speciality;
		Game::BoardManager::AnimationElement* current = NULL;
		CRGB previousPositionColor; // restore
	}

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
		void SetPlayerMapLed(MapPosition position, CRGB color)
		{
			if (Animation::current && Animation::current->position == position)
			{
				Animation::previousPositionColor = color;
			}
			else
			{
				Device::OutputManager::PlayerMapLed::Show(
					Device::MapManager::Translate(position),
					color);
			}
		}

		void ProcessAnimation();
		void ProcessAnimationElement();
		void ProcessCollect();
		void ProcessRunning();

		void UpdateCollect();
		void UpdateRunning();
		void UpdateSetup();

		void UpdateCollectLcd();
		void UpdateRunningLcd();
		void UpdateSetupLcd();

		void Process()
		{
			const unsigned long time = millis();
			dynamicStateData.timer += time - dynamicStateData.lastTime;
			dynamicStateData.lastTime = time;

			switch (Controller::GetState())
			{
			case GameState::Collect:
				ProcessCollect();

				break;
			case GameState::Running:
				ProcessRunning();

				break;
			}

			ProcessAnimation();
		}

		void ProcessAnimation()
		{
			if (Animation::current == NULL)
			{
				return;
			}

			if (dynamicStateData.timer > Animation::nextUpdate)
			{
				Device::OutputManager::PlayerMapLed::Show(
					Device::MapManager::Translate(Animation::current->position),
					Animation::previousPositionColor);
				++Animation::current;

				if (Animation::current->position == NULL)
				{
					switch (Animation::speciality)
					{
					case AnimationSpeciality::Running:
						Device::OutputManager::PlayerMapLed::Show(
							Device::MapManager::Translate(Game::GameManager::GetLastVillianPosition()),
							CRGB::White);

						break;
					}
				}

				ProcessAnimationElement();
			}
		}

		void ProcessAnimationElement()
		{
			Animation::previousPositionColor = Device::OutputManager::PlayerMapLed::_GetData()[Animation::current->position - 1];
			Animation::nextUpdate = dynamicStateData.timer + Animation::current->time;

			Device::OutputManager::PlayerMapLed::Show(
				Device::MapManager::Translate(Animation::current->position),
				Animation::current->color);
		}

		void ProcessCollect()
		{
			if (dynamicStateData.timer <= dynamicStateData.collect.nextUpdate)
			{
				return;
			}

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

		void ProcessRunning()
		{
			if (dynamicStateData.timer <= dynamicStateData.running.led.nextUpdate)
			{
				return;
			}

			const int currentPlayerIndex = GameManager::GetData()->state.activePlayerIndex;
			
			// powercounter to power
			// 255 - | counter - 255 |
			// h   - | counter - h   |
			const uint8_t power = dynamicStateData.running.led.powerCounter > 256
				? 0 
				: (128 - abs(dynamicStateData.running.led.powerCounter - 128));
			
			SetPlayerMapLed(currentPlayerIndex == 0
				? GameManager::GetLastVillianPosition()
				: GameManager::GetData()->player[currentPlayerIndex].position,
				ColorToCRGB(SetupManager::GetData()->playerContext.data[currentPlayerIndex]
					.color).subtractFromRGB(power)
			);

			Device::OutputManager::PlayerMapLed::Update();

			dynamicStateData.running.led.powerCounter %= 256;
			dynamicStateData.running.led.powerCounter += 256 * GAME_BOARDMANAGER_RUNNING_LEDSPEED / GAME_BOARDMANAGER_RUNNING_LEDSPEED_REP;

			dynamicStateData.running.led.nextUpdate = dynamicStateData.timer + GAME_BOARDMANAGER_RUNNING_LEDSPEED;
		}

		void Update()
		{
			DEBUG_MESSAGE("Update boardmanager");
			DEBUG_MESSAGE((int) Controller::GetState());

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
			UpdateCollectLcd();
		}

		void UpdateRunning()
		{
			DEBUG_MESSAGE("FLED Clear");
			Device::OutputManager::PlayerMapLed::Clear();
			
			DEBUG_MESSAGE("FLED Show1");
			// villian is shown as white
			if (Game::GameManager::GetData()->state.round >= 3 &&
				Game::GameManager::GetData()->state.activePlayerIndex != 0 &&
				!IsAnimationRunning())
			{
				SetPlayerMapLed(
					Game::GameManager::GetLastVillianPosition(),
					CRGB::White);
			}

			DEBUG_MESSAGE("FLED Show2");
			// skip villian (= 0)
			for (int i = 1; i < Collector::GetData()->playerCount; ++i)
			{
				SetPlayerMapLed(
					GameManager::GetData()->player[i].position,
					ColorToCRGB(SetupManager::GetData()->playerContext.data[i].color)
				);
			}

			
			DEBUG_MESSAGE("FLED Show3");
			for (int i = 0;
				i < (Game::GameManager::GetData()->state.round)
				  + (Game::GameManager::GetData()->state.activePlayerIndex != 0 ? 1 : 0); ++i)
			{
				Device::OutputManager::VillianPathLed::Show(
					i,
					ColorToCRGB(TicketToColor(
						Game::GameManager::GetData()->state.villianTicketUse[i]
					))
				);
			}

			DEBUG_MESSAGE("FLED Update");
			Device::OutputManager::PlayerMapLed::Update();

			UpdateRunningLcd();
		}

		void UpdateSetup()
		{
		}

		void UpdateCollectLcd()
		{
			Device::OutputManager::Lcd::Clear();
			Device::OutputManager::Lcd::DisplayLineType(
				0,
				message_collect_0
			);

			char lcdBuffer[DEVICE_LCD_WIDTH];

			sprintf_P(
				lcdBuffer,
				(char*)message_collect_1,
				Collector::GetData()->playerCount
			);

			Device::OutputManager::Lcd::DisplayLineType(
				1,
				lcdBuffer
			);
		}

		void UpdateRunningLcd()
		{
			DEBUG_MESSAGE("Lcd Update");
			Device::OutputManager::Lcd::Clear();
			Device::OutputManager::Lcd::DisplayLineType(
				0,
				message_running_0
			);

			char lcdBuffer[DEVICE_LCD_WIDTH];

			sprintf_P(
				lcdBuffer,
				(char*)message_running_1,
				Game::GameManager::GetData()->state.round + 1
			);

			Device::OutputManager::Lcd::DisplayLineType(
				1,
				lcdBuffer
			);

			sprintf_P(
				lcdBuffer,
				(char*)message_running_2,
				Game::GameManager::GetData()->state.activePlayer
			);

			Device::OutputManager::Lcd::DisplayLineType(
				2,
				lcdBuffer
			);
		}

		void UpdateSetupLcd()
		{
		}

		void RunAnimation(AnimationElement* const animation,
			AnimationSpeciality speciality)
		{
			Animation::speciality = speciality;

			if (Animation::current != NULL)
			{
				Device::OutputManager::PlayerMapLed::Show(
					Animation::current->position,
					Animation::previousPositionColor);
			}

			Animation::current = animation;

			if (Animation::current != NULL)
			{
				ProcessAnimationElement();
			}
		}

		bool IsAnimationRunning()
		{
			return Animation::current != NULL;
		}

		void OnStateChanged(const Game::GameState newState)
		{
			// abort animation on state change
			if (IsAnimationRunning())
			{
				RunAnimation(NULL);
			}

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
			case GameState::Running:
				dynamicStateData.running.led.nextUpdate = 0;
				dynamicStateData.running.led.powerCounter = 0;

				break;
			default:
				memset(&dynamicStateData, 0, sizeof(dynamicStateData));

				break;
			}
		}
		
		void ReloadLcd()
		{
			switch (Controller::GetState())
			{
			case GameState::Collect:
				UpdateCollectLcd();

				break;
			case GameState::Running:
				UpdateRunningLcd();

				break;
			}
		}
	}
}
