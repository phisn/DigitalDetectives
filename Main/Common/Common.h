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

// general string type
typedef const __FlashStringHelper* FlashString;

#ifdef __INTELLISENSE__
// placement new fix
inline void* operator new(unsigned, void* ptr)
{
	return ptr;
}
#endif

// common definitions
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

#define COMMON_MAX_PLAYERCOUNT 6
#define COMMON_MAP_SIZE 199

// wrong intellisense include fix
#ifdef __INTELLISENSE__
#define INCL_ARDU(intel, real) intel
#else
#define INCL_ARDU(intel, real) real
#endif

#ifdef VM_DEBUG
#define DEBUG_MESSAGE(message) Serial.println(message)
#else
#define DEBUG_MESSAGE(message) (void) 0
#endif

// ws2812b
// #define FASTLED_ALLOW_INTERRUPTS 0
#define FASTLED_INTERNAL
#define FASTLED_ESP8266_RAW_PIN_ORDER

#include <FastLED.h>
