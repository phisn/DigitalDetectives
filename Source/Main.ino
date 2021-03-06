#include "Common/Common.h"
#include "Device/DeviceManager.h"
#include "Device/OutputManager.h"
#include "Device/MapManager.h"
#include "Game/GameController.h"
#include "Device/DevicePins.h"

#include <esp_core_dump.h>

namespace EOBJ
{
	EEPROMClass* EEPROM = &::EEPROM;
	WiFiClass* WiFi = &::WiFi;
	CFastLED* FastLED = &::FastLED;
}

/*
Info
- Some position are different in two versions of
  scotlandyard. These do not affect the starting
  positions! more info(https://boardgamegeek.com/thread/77052/starting-places)
- All data should be stored as PROGMEM and strings
  should use the definition FlashString defined in
  Common/Common.h
  -> Data stored in PROGMEM cant just be read
  -> FlashString do have to be either used in function
	 with the suffix "_P" (preferred) or be converted into
	 normal readable char arrays
  -> Raw data has to be read using pgm_read_xxx byte by byte
	 or retrieved with memcpy_P [usally a good idea if u have
	 many same size PROGMEM data and want to load in a buffer
	 (not parrallel)]
  -> more info at (https://arduino-esp8266.readthedocs.io/en/latest/PROGMEM.html)
- All faults and failures should have a recognizable
  FailureId (short FID in definitions [ex. OutputManger])
  -> Error messages can be max. 30 characters long
  -> FailureId can be max. 7 digits long (DEC)
  -> Module names are predefined in faulthandler
- There are two types of orders in processing and managment
  -> The first order exists in InterfaceManager. First player
	 joined gets first place because the order does not matter.
	 It is simply used to process player interfaces
  -> The second order exists in the Setup / Game. This on is used to
	 identify the order of players in the running game. It is semi random
	 because the villian always gets a specific place and the
	 detectives are placed randomly
*/

void setup()
{
	Serial.begin(9600);

	DEBUG_MESSAGE("ESP8266 Boot");
	Device::GameManager::Initialize();
}

void loop()
{
	Device::GameManager::Process();
}

// external functions needed to be run in ino main file
void Device::OutputManager::_InitializeFastLed()
{
	DEBUG_MESSAGE("FastLED Init");

	memset(Device::OutputManager::PlayerMapLed::_GetData(), 0,
		sizeof(CRGB) * DEVICE_FASTLED_MAP_LEDCOUNT);
	memset(Device::OutputManager::VillianPathLed::_GetData(), 0,
		sizeof(CRGB) * DEVICE_FASTLED_PATH_LEDCOUNT);

	FastLED.addLeds<WS2812B, DEVICE_PIN_OUTPUT_FASTLED_0, GRB>(
		Device::OutputManager::PlayerMapLed::_GetData(), DEVICE_FASTLED_MAP_LEDCOUNT);
	FastLED.addLeds<WS2812B, DEVICE_PIN_OUTPUT_FASTLED_1, GRB>(
		Device::OutputManager::VillianPathLed::_GetData(), DEVICE_FASTLED_PATH_LEDCOUNT);

	FastLED.setBrightness(50);
	FastLED.show();
}
