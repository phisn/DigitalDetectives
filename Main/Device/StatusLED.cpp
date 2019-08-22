#include "StatusLED.h"

#include "../Device/DevicePins.h"

namespace Device
{
	namespace StatusLED
	{
		void Initialize()
		{
			pinMode(DEVICE_STATUS_LED, OUTPUT);
		}

		void Unintialize()
		{
		}
	}
}
