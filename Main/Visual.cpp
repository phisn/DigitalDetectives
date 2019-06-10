#include "Visual.h"

#ifdef __INTELLISENSE__
#include <LiquidCrystal/src/LiquidCrystal.h>
#else
#include <LiquidCrystal.h>
#endif

namespace
{
	LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
}

namespace Visual
{
	void Initialize()
	{
		lcd.begin(16, 2);
	}

	void LCD::Print(const char* message)
	{
		lcd.setCursor(0, 0);
		lcd.println(message);
	}

	void LCD::Print(const char* line1, const char* line2)
	{
		lcd.setCursor(0, 0);
		lcd.println(line1);

		lcd.setCursor(0, 1);
		lcd.println(line2);
	}
}
