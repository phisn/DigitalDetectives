#include "OutputManager.h"
#include "../Device/DevicePins.h"

namespace
{
	LiquidCrystal_I2C lcd{ 0x27, 20, 4 };

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
			InitializeLcd();
			InitializeFastLed();
		}

		void InitializeLcd()
		{
			lcd.init();
			lcd.backlight();
		}

		void InitializeFastLed()
		{
			FastLED.addLeds<WS2812B, DEVICE_PIN_OUTPUT_FASTLED>(
				mapLeds, DEVICE_FASTLED_MAP_LEDCOUNT
			);
		}

		void Uninitialize()
		{
		}

		void Lcd::Clear()
		{
			lcd.clear();
		}

		LiquidCrystal_I2C* Lcd::_GetDisplay()
		{
			return &lcd;
		}
	}
}
