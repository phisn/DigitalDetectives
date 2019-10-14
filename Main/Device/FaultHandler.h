#pragma once

#include "../Device/FailureHandler.h"
#include "../Device/MemoryManager.h"
#include "../Device/OutputManager.h"

#define DEVICE_EMESSAGE_ERROR "Error: "
#define DEVICE_EMESSAGE_ERROR_NONFATAL "Wrnng: "
#define DEVICE_EMESSAGE_ERROR_FATAL "Fatal: "

#define DEVICE_EMESSAGE_MODULE "Module: "
#define DEVICE_EMESSAGE_FID "FailureId: "

// minus null byte
#define DEVICE_EMESSAGE_ERROR_LEN (sizeof(DEVICE_EMESSAGE_ERROR) - 1)
#define DEVICE_EMESSAGE_MESSAGE_LEN (DEVICE_LCD_WIDTH * 2 - sizeof(DEVICE_EMESSAGE_ERROR) - 1)

// usage: FlashString fault_xxx = DEVICE_FAULT_MESSAGE("xxx");
#define DEVICE_FAULT_MESSAGE(txt) FPSTR(txt); static_assert(sizeof(txt) == DEVICE_EMESSAGE_MESSAGE_LEN, \
	"Fault message has to be have full length (see DEVICE_EMESSAGE_MESSAGE_LEN)")

#define DEVICE_MIN_REMAIN_MEMORY 128
#define DEVICE_MAX_HEAP_FRAGMENT 50 // in percent

namespace Device
{
	enum class FaultModule
	{
		FaultHandler,
		NetworkManager,
		MapManager,

		BoardManager,
		Collector,
		SetupManager,
		GameManager,
		GameController,

		InterfaceManager,
		RequestHandler,
		WebInterface,

		_Length
	};
	
	struct Fault
	{
		FaultModule module;
		FailureId id;
		FlashString text;
	};

	namespace FaultHandler
	{
		struct FID
		{
			// FailureIds over _Length represent faultmodules index 
			// by i + _Length -> first is at _Length

			enum
			{
				INC_NULL = 2, // interfacenotifiercallback
				LOW_MEMORY,
				HEAP_FRAG,
				_Length // for fault module conversion in HandleCommonFault
			};
		};

		typedef void (*InterfaceNotifierCallback)(const Fault);

		// called in interfacemanager
		void RegisterInterfaceNotifier(
			const InterfaceNotifierCallback callback);

		void Initialize();
		void Unintialize();

		void Report(); // -> eeprom
		// faults can be non-fatal to continue normally
		void Handle(const Fault fault, const bool fatal);
		void ValidateDeviceState();
	}
}
