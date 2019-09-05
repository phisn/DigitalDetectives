#pragma once

#include "../Device/FailureHandler.h"
#include "../Device/MemoryManager.h"

#define DEVICE_LCD_ADDRESS 0x27
#define DEVICE_LCD_WIDTH 20
#define DEVICE_FASTLED_MAP_LEDCOUNT 199

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

				if (_GetDisplay()->getWriteError())
				{
					FailureHandler::Handle(
						Device::FailureModule::OutputManager,
						FID::LCD_DISPLAY
					);
				}

			}

			void Clear();
		}
	}
}
