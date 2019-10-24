#pragma once

#include "../Device/FailureHandler.h"
#include "../Device/MemoryManager.h"

#define DEVICE_LCD_ADDRESS 0x27
#define DEVICE_LCD_WIDTH 20
#define DEVICE_FASTLED_MAP_LEDCOUNT 199

#define DEVICE_LCD_MESSAGE(txt) FPSTR(txt); static_assert(sizeof(txt) - 1 == DEVICE_LCD_WIDTH, \
	"LCD message has to be have the length of LCD width (see DEVICE_LCD_WIDTH)")


namespace Device
{
	namespace OutputManager
	{
		struct FID
		{
			enum
			{
				LCD_DISPLAY = 3
			};
		};

		void Initialize();
		void Uninitialize();

		namespace Interact
		{
			enum Choice
			{
				Empty	= 0b00000000,
				Yes		= 0b00000001,
				No		= 0b00000010,
				Cancel	= 0b00000100
			};

			Choice GetChoice();
			Choice ForceGetChoice();
		}

		namespace Lcd
		{
			LiquidCrystal_I2C* _GetDisplay();

			template <typename T>
			void DisplayLineType(
				const unsigned char row,
				const T value)
			{
				_GetDisplay()->setCursor(0, row);
				_GetDisplay()->print(value);
			}

			void DisplayLineType(
				const unsigned char row,
				const char* value,
				const unsigned int size);

			void Clear();
		}

		namespace FastLed
		{
			void Clear();
			void Show(const int pin, CRGB color);
			void Update();
		}
	}
}
