#include "Common.h"

#include "Host.h"
#include "Visual.h"

#include INCL_ARDU("FastLED/FastLED.h", "FastLED.h")

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
