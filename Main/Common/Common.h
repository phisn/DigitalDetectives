#pragma once

#include <Arduino.h>
#include <Esp.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include <FastLED.h>

typedef const __FlashStringHelper* FlashString;

#ifdef __INTELLISENSE__
#define INCL_ARDU(intel, real) intel
#else
#define INCL_ARDU(intel, real) real
#endif

// #define FASTLED_ESP8266_NODEMCU_PIN_ORDER
#define FASTLED_ESP8266_RAW_PIN_ORDER
