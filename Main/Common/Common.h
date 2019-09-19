#pragma once

// internal
#include <Arduino.h>
#include <Esp.h>
#include <EEPROM.h>

// wifi
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// lcd
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// common definitions
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

// ws2812b
// #define FASTLED_ALLOW_INTERRUPTS 0
#define FASTLED_INTERNAL
#define FASTLED_ESP8266_RAW_PIN_ORDER

#include <FastLED.h>

#ifdef __INTELLISENSE__
#define INCL_ARDU(intel, real) intel
#else
#define INCL_ARDU(intel, real) real
#endif
