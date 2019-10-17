#include "OutputManager.h"
#include "../Device/DevicePins.h"

namespace EOBJ
{
	extern CFastLED* FastLED;
}

namespace
{
	CRGB mapLeds[DEVICE_FASTLED_MAP_LEDCOUNT];
}

namespace Device
{
	namespace OutputManager
	{
		void InitializeLcd();
		void InitializeFastLed();

		void Initialize()
		{
			DEBUG_MESSAGE("Output Init");

			InitializeLcd();
			InitializeFastLed();
		}

		void InitializeLcd()
		{
			DEBUG_MESSAGE("LCD Init");

			Wire.begin(D5, D4);
			
			Lcd::_GetDisplay()->init();
			Lcd::_GetDisplay()->backlight();

			Lcd::Clear();
		}

		void InitializeFastLed()
		{
			DEBUG_MESSAGE("FastLED Init");

			EOBJ::FastLED->addLeds<WS2812B, DEVICE_PIN_OUTPUT_FASTLED>(
				mapLeds, DEVICE_FASTLED_MAP_LEDCOUNT
			);
		}

		void Uninitialize()
		{
		}

		namespace Interact
		{
			Choice GetChoice()
			{
			}

			Choice ForceGetChoice()
			{
				Choice choice;

				while (true)
				{
					choice = GetChoice();

					if (choice != Choice::Empty)
					{
						break;
					}

					delay(500);
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
				DEBUG_MESSAGE("ptr");
				DEBUG_MESSAGE((int) value);
				DEBUG_MESSAGE((int)((const uint8_t*) value));

				DEBUG_MESSAGE((int)_GetDisplay);
				DEBUG_MESSAGE((int)((Print*)_GetDisplay()));

				((Print*) 1073677524)->write((const uint8_t*) value, size);
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
		}
	}
}

void Device::OutputManager::FastLed::Clear()
{
	for (int i = 0; i < COMMON_MAP_SIZE; ++i)
	{
		mapLeds[i] = CRGB::Black;
	}
}

void Device::OutputManager::FastLed::Show(const int pin, CRGB color)
{
	mapLeds[pin - 5] = color;
}

void Device::OutputManager::FastLed::Update()
{
	EOBJ::FastLED->show();
}
