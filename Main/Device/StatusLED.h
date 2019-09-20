#pragma once

#pragma pack(push, 1)

#include "../Common/Common.h"

#define DEVICE_TIMEOUT_COLOR (Device::RGB{ HIGH, LOW, HIGH })

namespace Device
{
	// special delay / timeout
	// bound to StatusLED
	void Timeout(const unsigned long time)
	{
		RGB old = StatusLED::GetCurrent();

		StatusLED::Show(DEVICE_TIMEOUT_COLOR);
		delay(time);
		StatusLED::Show(old);
	}

	namespace StatusLED
	{
		void Initialize();
		void Unintialize();

		void Show(const RGB color);

		RGB GetCurrent();
	}
}

#pragma push(pop)
