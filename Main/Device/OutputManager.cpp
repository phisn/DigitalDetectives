#include "OutputManager.h"
#include "../Device/DevicePins.h"

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
			InitializeLcd();
			// InitializeFastLed();
		}

		void InitializeLcd()
		{
			Wire.begin(D5, D4);
			
			Lcd::_GetDisplay()->init();
			Lcd::_GetDisplay()->backlight();
		
			delay(500);
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
			//lcd.clear();
		}

		LiquidCrystal_I2C* Lcd::_GetDisplay()
		{
			// fix bug
			static LiquidCrystal_I2C lcdi2c(0x27, 20, 4);
			return &lcdi2c;
		}
	}
}
