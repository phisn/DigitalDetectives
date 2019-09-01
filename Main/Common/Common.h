#pragma once

#include <Arduino.h>
#include <Esp.h>

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

typedef const __FlashStringHelper* FlashString;

#define COMMON_MAP_SIZE 199

namespace Game
{
	typedef unsigned char MapPosition;
}

namespace Device
{
	struct RGB
	{
		unsigned char r, g, b;
	};
}

#define FASTLED_INTERNAL
#define FASTLED_ESP8266_RAW_PIN_ORDER

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include <FastLED.h>

#ifdef __INTELLISENSE__
#define INCL_ARDU(intel, real) intel
#else
#define INCL_ARDU(intel, real) real
#endif
