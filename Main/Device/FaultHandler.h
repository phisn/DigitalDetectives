#pragma once

#include "../Device/FailureHandler.h"
#include "../Device/MemoryManager.h"

namespace Device
{
	enum class FaultModule
	{
		NetworkManager,
		MapManager,
		BoardManager,
		GameManager,
		GameAccess,
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
				_Length // for fault module conversion in HandleCommonFault
			};
		};

		typedef void (*InterfaceNotifierCallback)(const Fault);

		// called in interfacemanager
		void RegisterInterfaceNotifier(
			const InterfaceNotifierCallback callback);

		void Initialize();
		void Unintialize();

		void Handle(const Fault fault);
	}
}
