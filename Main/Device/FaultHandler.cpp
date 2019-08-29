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



namespace Device
{
	namespace FaultHandler
	{
		void DisplayFaultMessage(
			const FaultModule module,
			FlashString text,
			const FailureId id);

		void Initialize()
		{
		}

		void Unintialize()
		{
		}

		void Handle(
			const FaultModule module, 
			FlashString text,
			const FailureId id)
		{
		}

		void DisplayFaultMessage(
			const FaultModule module,
			FlashString text,
			const FailureId id)
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
	}
}

