#pragma once

#include <Arduino.h>
#include <Esp.h>

#ifdef __INTELLISENSE__
#define INCL_ARDU(intel, real) intel
#else
#define INCL_ARDU(intel, real) real
#endif

#define FASTLED_ESP8266_RAW_PIN_ORDER
