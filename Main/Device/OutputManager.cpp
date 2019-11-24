#include "OutputManager.h"
#include "../Device/DevicePins.h"

namespace EOBJ
{
	extern CFastLED* FastLED;
}

namespace
{
	CRGB data[DEVICE_FASTLED_MAP_LEDCOUNT];
}

namespace Device
{
	namespace OutputManager
	{
		void InitializeLcd();

		void Initialize()
		{
			DEBUG_MESSAGE("Output Init");

			InitializeLcd();
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