#include "OutputManager.h"
#include "../Device/DevicePins.h"

namespace EOBJ
{
	extern CFastLED* FastLED;
}

namespace
{
	CRGB data[DEVICE_FASTLED_MAP_LEDCOUNT];

	FlashString common_yesno = DEVICE_LCD_MESSAGE(" Yes             NO ");
}

namespace Device
{
	namespace OutputManager
	{
		void InitializeLcd();
		void InitializeInteract()
		{
			pinMode(DEVICE_PIN_BUTTON_LEFT, INPUT_PULLDOWN);
			pinMode(DEVICE_PIN_BUTTON_ENTER, INPUT_PULLDOWN);
			pinMode(DEVICE_PIN_BUTTON_RIGHT, INPUT_PULLDOWN);
		}

		void Initialize()
		{
			DEBUG_MESSAGE("Output Init");

			InitializeLcd();
			InitializeInteract();
			_InitializeFastLed();
		}

		void InitializeLcd()
		{
			DEBUG_MESSAGE("LCD Init");

			Wire.begin(DEVICE_PIN_LCD_SDA, DEVICE_PIN_LCD_SCL);
			
			Lcd::_GetDisplay()->init();
			Lcd::_GetDisplay()->backlight();

			Lcd::Clear();
		}

		void Uninitialize()
		{
		}

		namespace Interact
		{
			FlashString GetCommonYesNo()
			{
				return common_yesno;
			}

			int Select(FlashString* const selection, const int size)
			{
				int index = 0, cursor = 0;
				char lcdBuffer[DEVICE_LCD_WIDTH + 1] = { };
				
				// init buffer
				memset(lcdBuffer, ' ', DEVICE_LCD_WIDTH);
				lcdBuffer[DEVICE_LCD_WIDTH] = '\0';

				bool needsUpdate = true;

				while (true)
				{
					if (needsUpdate)
					{
						needsUpdate = false;

						for (int i = 0; i < 4; ++i)
						{
							lcdBuffer[DEVICE_LCD_WIDTH - 3] = ' ';

							if (cursor == i)
							{
								lcdBuffer[0] = '>';
								memcpy_P(lcdBuffer + 1, (const char*)(selection[index + i]), DEVICE_SELECTION_SIZE);
							}
							else
							{
								memcpy_P(lcdBuffer, (const char*)(selection[index + i]), DEVICE_SELECTION_SIZE);
							}

							if (size > 4)
							{
								switch (i)
								{
								case 0:
									if (index > 0)
									{
										lcdBuffer[DEVICE_LCD_WIDTH - 1] = '^';
									}
									else
									{
										lcdBuffer[DEVICE_LCD_WIDTH - 1] = '-';
									}

									break;
								case 3:
									if (index < size - 4)
									{
										lcdBuffer[DEVICE_LCD_WIDTH - 1] = 'v';
									}
									else
									{
										lcdBuffer[DEVICE_LCD_WIDTH - 1] = '-';
									}

									break;
								default:
									lcdBuffer[DEVICE_LCD_WIDTH - 1] = '|';

									break;
								}
							}

							Lcd::DisplayLineType(i, lcdBuffer);
						}

						delay(300);
					}

					delay(50);
					
					const Choice choice = ForceGetChoice();

					switch (choice)
					{
					case Left:
						if (cursor > 0)
						{
							--cursor;

							needsUpdate = true;
						}
						else if (index > 0)
						{
							--index;

							needsUpdate = true;
						}

						break;
					case Enter:
						return index + cursor;

					case Right:
						if (index + cursor < size - 1)
						{
							if (cursor < DEVICE_LCD_HEIGHT - 1)
							{
								++cursor;
							}
							else
							{
								++index;
							}

							needsUpdate = true;
						}

						break;
					default:
						break;
					}
				}

				return index;
			}

			Choice GetChoice()
			{
				Choice result = Empty;

				if (digitalRead(DEVICE_PIN_BUTTON_LEFT) == HIGH)
				{
					(int&) result |= Left;
				}

				if (digitalRead(DEVICE_PIN_BUTTON_ENTER) == HIGH)
				{
					(int&) result |= Enter;
				}

				if (digitalRead(DEVICE_PIN_BUTTON_RIGHT) == HIGH)
				{
					(int&) result |= Right;
				}

				return result;
			}

			Choice ForceGetChoice()
			{
				Choice choice;

				while (true)
				{
					choice = GetChoice();

					if (choice != Choice::Empty 
						&& (choice == Left ||
							choice == Right ||
							choice == Enter))
					{
						break;
					}

					delay(50);
				}

				return choice;
			}
		}

		namespace Lcd
		{
			void DisplayLineType(
				const unsigned char row, 
				const char* value, 
				const unsigned int size)
			{
				_GetDisplay()->setCursor(0, row);

				for (int i = 0; i < size; ++i)
				{
					_GetDisplay()->write((uint8_t)value[i]);
				}
			}

			void Clear()
			{
				_GetDisplay()->clear();
			}

			LiquidCrystal_I2C* _GetDisplay()
			{
				// fix bug
				// static __attribute__((aligned(4))) 
				static LiquidCrystal_I2C* lcdi2c = new LiquidCrystal_I2C(
					DEVICE_LCD_ADDRESS,
					DEVICE_LCD_WIDTH, 4);
				return lcdi2c;
			}
			FlashString GetCommonYesNo()
			{
				return FlashString();
			}
		}

		namespace FastLed
		{
			void Clear()
			{
				EOBJ::FastLED->clearData();
			}

			void Show(const int pin, CRGB color)
			{
				data[pin] = color;
			}

			void Update()
			{
				FastLED.show();
			}

			CRGB* _GetData()
			{
				return data;
			}
		}
	}
}