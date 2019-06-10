#include <power_mgt.h>
#include <platforms.h>
#include <pixeltypes.h>
#include <pixelset.h>
#include <noise.h>
#include <lib8tion.h>
#include <led_sysdefs.h>
#include <hsv2rgb.h>
#include <fastspi_types.h>
#include <fastspi_ref.h>
#include <fastspi_nop.h>
#include <fastspi_dma.h>
#include <fastspi_bitbang.h>
#include <fastspi.h>
#include <fastpin.h>
#include "Host.h"
#include "Visual.h"

#ifdef __INTELLISENSE__
#include "FastLED/FastLED.h"
#else
#include "FastLED.h"
#endif

#define ANZAHL_LEDS 1
#define LED_PIN D8
CRGB leds[ANZAHL_LEDS];

void setup() {
	FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, ANZAHL_LEDS);
}

void loop() {
	leds[0] = CRGB::Red;
	FastLED.show();
	delay(1000);
	leds[0] = CRGB::Blue;
	FastLED.show();
	delay(1000);
	leds[0] = CRGB::Green;
	FastLED.show();
	delay(1000);
	leds[0] = CRGB::Yellow;
	FastLED.show();
	delay(1000);
	leds[0] = CRGB::Black;
	FastLED.show();
	delay(1000);
}
