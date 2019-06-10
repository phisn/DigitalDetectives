#include "Host.h"
#include "FaultHandler.h"

#ifdef __INTELLISENSE__
#include <ESP8266WiFi/src/ESP8266WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif

namespace Host
{
	void onGetPlayerCount(const char* data);
}

const Host::Request requests[] PROGMEM =
{
	Host::onGetPlayerCount
};

namespace Host
{
	void onGetPlayerCount(const char* data)
	{
	}

	void Initialize()
	{
		if (!WiFi.softAP(
				NETWORK_NAME,
				NETWORK_PASS,
				NETWORK_CHANNEL,
				NETWORK_HIDE_SSID,
				NETWORK_MAX_CONN))
		{
			FaultHandler::RebootDevice(
				""
//				FPSTR(str)
			);
		}


	}

	void HandleRequest(
		const Common::RequestType requestType, 
		const char* data)
	{
		requests[(int) requestType](data);
	}
}
