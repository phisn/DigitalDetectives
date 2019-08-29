#include "FaultHandler.h"

namespace
{
	FlashString emessageError = FPSTR(PSTR("Error: "));
	FlashString emessageModule = FPSTR(PSTR("Module: "));
	FlashString emessageFID = FPSTR(PSTR("FailureId: "));

	FlashString emessageModuleNames[(int) Device::FaultModule::_Length][12] PROGMEM = // 11 + \0
	{
		FPSTR(PSTR("InterfaceMg")),
		FPSTR(PSTR("NetworkMg  ")),
		FPSTR(PSTR("MapManager ")),
		FPSTR(PSTR("BoardMg    ")),
		FPSTR(PSTR("GameAccess ")),
		FPSTR(PSTR("RequestHndl")),
		FPSTR(PSTR("WebInt     "))
	};
}

// ################### <- 20
// ########            <- 9
//         ########### <- 11 
// Module: InterfaceMg   
// Module: NetworkMg
// Module: MapManager
// Module: BoardMg
// Module: GameAccess
// Module: RequestHndl
// Module: WebInt

/*
		NetworkManager,
		MapManager,
		BoardManager,
		GameManager,
		GameAccess,
		InterfaceManager,
		RequestHandler,
		WebInterface
*/

/*

ErrorMessage:
	vvvvvvvvvvvvvvvvvvv
   >Error: ############ <- 12 ch error message
   >################### <- + 20 ch -> 30 ch
   >Module: ########### <- 11 ch module name
   >FailureId: ######## <- 7 digits for failure id
    ^^^^^^^^^^^^^^^^^^^
*/

namespace
{
	Device::FaultHandler::InterfaceNotifierCallback interfaceNotifierCallback = NULL;
}

namespace Device
{
	namespace FaultHandler
	{
		void DisplayFaultMessage(const Fault fault);
		void HandleModuleFault(const Fault fault);
		void HandleCommonFault(const Fault fault);

		void RegisterInterfaceNotifier(
			const InterfaceNotifierCallback callback)
		{
			interfaceNotifierCallback = callback;
		}

		void Initialize()
		{
		}

		void Unintialize()
		{
		}

		void Handle(const Fault fault)
		{
			if (interfaceNotifierCallback == NULL)
			{
				FailureHandler::Handle(
					FailureModule::FaultHandler,
					FID::INC_NULL
				);
			}

			DisplayFaultMessage(fault);
			interfaceNotifierCallback(fault);

			HandleModuleFault(fault);
		}

		void DisplayFaultMessage(const Fault fault)
		{
			OutputManager::Lcd::DisplayLineType(
				0,
				emessageError);
			// add error message
			OutputManager::Lcd::DisplayLineType(
				2,
				emessageModule);
			// add module name
			OutputManager::Lcd::DisplayLineType(
				0,
				emessageFID);
			// add fid number
		}

		void HandleModuleFault(const Fault fault)
		{
			switch (fault.module)
			{
			default:
				HandleCommonFault(fault);
			}
		}

		void HandleCommonFault(const Fault fault)
		{
			FailureHandler::Handle(
				FailureModule::FaultHandler,
				FID::_Length + (int) fault.module
			);
		}
	}
}

