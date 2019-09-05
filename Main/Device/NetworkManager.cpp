#include "NetworkManager.h"

/*

	WiFi info:	(https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/readme.html)
	sAP info:	(https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/soft-access-point-class.html)
	Web info:	(https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WebServer)

*/

namespace
{
	FlashString ssid = FPSTR(DEVICE_NET_SSID);
	FlashString pass = FPSTR(DEVICE_NET_PASS);

	FlashString fault_soft_ap_config = DEVICE_FAULT_MESSAGE("Failed to set SoftAP config   ");
	FlashString fault_soft_ap_create = DEVICE_FAULT_MESSAGE("Failed to create SoftAP       ");

	ESP8266WebServer server;
}

// Number of connections is limited (sAP info)
static_assert(DEVICE_NET_MAX_CONN >= 0 && DEVICE_NET_MAX_CONN <= 8,
	"DEVICE_NET_MAX_CONN cant be smaller than 0 or higher than 8!");

namespace Device
{
	namespace NetworkManager
	{
		void Initialize()
		{
			if (!WiFi.mode(WiFiMode::WIFI_AP))
			{
				// ...
			}

			IPAddress local_ip DEVICE_NET_LOCAL_IP;
			IPAddress subnet_mask DEVICE_NET_SUBNET_MASK;

			if (!WiFi.softAPConfig(
					local_ip,
					local_ip,
					subnet_mask))
			{
				FaultHandler::Handle(
					{
						FaultModule::NetworkManager,
						(FailureId) FID::SOFT_AP_CONFIG,
						fault_soft_ap_config
					});
			}

			char ssidBuffer[sizeof(DEVICE_NET_SSID)];
			char passBuffer[sizeof(DEVICE_NET_PASS)];

			memcpy_P(ssidBuffer, ssid, sizeof(DEVICE_NET_SSID));
			memcpy_P(passBuffer, pass, sizeof(DEVICE_NET_PASS));

			if (!WiFi.softAP(
					ssidBuffer,
					pass,
					DEVICE_NET_CHANNEL,
					DEVICE_NET_SSID_HIDDEN,
					DEVICE_NET_MAX_CONN))
			{
				FaultHandler::Handle(
					{
						FaultModule::NetworkManager,
						(FailureId) FID::SOFT_AP_CREATE,
						fault_soft_ap_create
					});
			}

			server.begin(80);
		}

		void Unintialize()
		{
			// WiFi.softAPdisconnect();
		}

		StationCount GetStationCount()
		{
			return WiFi.softAPgetStationNum();
		}

		void Process()
		{
			server.handleClient();
		}
	}
}
