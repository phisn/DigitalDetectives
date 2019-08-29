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

	namespace FaultHandler
	{
		void Initialize();
		void Unintialize();

		void Handle(
			const FaultModule module,
			const char* text,
			const FailureId id
		);
	}
}
