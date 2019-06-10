#include "FaultHandler.h"
#include <Esp.h>

void FaultHandler::RebootDevice(PGM_P reason)
{
	LogVisual("");
	ESP.restart();
}

void FaultHandler::Log(PGM_P message)
{
#ifdef _DEBUG
	Serial.println(message);
#endif
}

void FaultHandler::LogVisual(PGM_P message)
{
	Log(message);

	// print to lcd
	// wait short time _or_ button
}
