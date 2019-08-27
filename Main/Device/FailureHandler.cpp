#include "FailureHandler.h"

namespace Device
{
	namespace FailureHandler
	{
		void HandleFatalError();

		void HandleMemoryFailure(const FailureId id);
		void HandleOutputFailure(const FailureId id);
		void HandleFaultFailure(const FailureId id);

		void DisplayFailureStatus(
			const RGB color,
			const FailureId id);

		void Initialize()
		{
		}

		void Unintialize()
		{
		}


		void Handle(const FailureModule module, const FailureId id)
		{
			switch (module)
			{
			case FailureModule::MemoryManager:
				HandleMemoryFailure(id);

				break;
			case FailureModule::OutputManager:
				HandleOutputFailure(id);

				break;
			case FailureModule::FaultHandler:
				HandleFaultFailure(id);

				break;
			}
		}

		void HandleMemoryFailure(const FailureId id)
		{
			DisplayFailureStatus(DEVICE_MEMORY_MANAGER_COLOR, id);
			HandleFatalError();
		}

		void HandleOutputFailure(const FailureId id)
		{
			DisplayFailureStatus(DEVICE_OUTPUT_MANAGER_COLOR, id);
			HandleFatalError();
		}

		void HandleFaultFailure(const FailureId id)
		{
			if (id != 0)
			{
				DisplayFailureStatus(DEVICE_FAULT_MANAGER_COLOR, id);
			}

			HandleFatalError();
		}

		void HandleFatalError()
		{
			ESP.restart();
		}

		void DisplayFailureStatus(
			const RGB color,
			const FailureId id)
		{
			for (int i = 0; i < 3; ++i)
			{
				for (FailureId i = 0; i < id; ++i)
				{
					StatusLED::Show(color);
					delay(400);
					StatusLED::Show(RGB{ LOW, LOW, LOW });
					delay(400);
				}

				delay(2000);
			}
		}
	}
}
