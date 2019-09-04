#pragma once

#include "../Device/StatusLED.h"

#define DEVICE_UNKOWN_COLOR  (Device::RGB{ HIGH, LOW, HIGH })

#define DEVICE_MEMORY_MANAGER_COLOR (Device::RGB{ HIGH, LOW, LOW })
#define DEVICE_OUTPUT_MANAGER_COLOR (Device::RGB{ LOW, HIGH, LOW })
#define DEVICE_FAULT_MANAGER_COLOR (Device::RGB{ LOW, LOW, HIGH })

namespace Device
{
	typedef unsigned char FailureId;

	enum class FailureModule : unsigned char
	{
		MemoryManager,
		OutputManager,
		FaultHandler
	};

	namespace FailureHandler
	{
		void Initialize();
		void Unintialize();

		void Handle(
			const FailureModule module,
			const FailureId id);
	}
}
