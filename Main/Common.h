#pragma once

#define RESOURCE_BEGIN __pragma(pack(push, 1))
#define RESOURCE_END __pragma(pack(pop))

#ifdef __INTELLISENSE__
#define INCL_ARDU(intel, real) intel
#else
#define INCL_ARDU(intel, real) real
#endif

#define FASTLED_ESP8266_RAW_PIN_ORDER
