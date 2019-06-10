#pragma once

namespace Common // export
{
	enum class RequestType
	{
		GetPlayerCount,
		GetLastCriminalPosition,
		GetDetectivePosition
	};
}

#define NETWORK_NAME F("DigitalDetective")
#define NETWORK_PASS F("DD")
#define NETWORK_CHANNEL 6
#define NETWORK_HIDE_SSID 1
#define NETWORK_MAX_CONN 8

namespace Host
{
	typedef void (*Request)(const char* data);

	void Initialize();

	void HandleRequest(
		const Common::RequestType requestType,
		const char* data);
}
