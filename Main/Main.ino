#include "Device/DeviceManager.h"

/*

Info:
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

*/

void setup()
{
	Device::Manager::Initialize();
}

void loop()
{
	Device::Manager::Process();
}

