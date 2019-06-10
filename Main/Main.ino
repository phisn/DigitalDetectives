#include "Host.h"
#include "Visual.h"

#include <ESP8266WiFi.h>

void setup()
{
	Serial.begin(115200);
	Serial.println();

	Serial.print("Setting soft-AP ... ");
	boolean result = WiFi.softAP(
		NETWORK_NAME,
		NETWORK_PASS);
	if (result == true)
	{
		Serial.println("Ready");
	}
	else
	{
		Serial.println("Failed!");
	}
}

void loop()
{
	Serial.printf("Stations connected = %d\n", WiFi.softAPgetStationNum());
	delay(3000);
}