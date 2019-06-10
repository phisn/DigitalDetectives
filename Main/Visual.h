#pragma once

// lcd pins
#define LCD_RS 0
#define LCD_EN 0
#define LCD_D4 0
#define LCD_D5 0
#define LCD_D6 0
#define LCD_D7 0

namespace Visual
{
	void Initialize();

	namespace LCD
	{
		void Print(const char* message);
		void Print(const char* line1, const char* line2);
	}

	namespace LED
	{

	}

	namespace WS2812B
	{

	}
}
