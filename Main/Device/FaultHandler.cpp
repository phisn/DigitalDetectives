#include "FaultHandler.h"

// minus null byte
#define DEVICE_EMESSAGE_ERROR_LEN sizeof(DEVICE_EMESSAGE_ERROR) - 1
#define DEVICE_EMESSAGE_MODULE_LEN sizeof(DEVICE_EMESSAGE_MODULE) - 1
#define DEVICE_EMESSAGE_FID_LEN sizeof(DEVICE_EMESSAGE_FID) - 1

#define DEVICE_EMESSAGE_MESSAGE_LEN_FL DEVICE_LCD_WIDTH - DEVICE_EMESSAGE_ERROR_LEN
#define DEVICE_EMESSAGE_MODULE_NAME_LEN DEVICE_LCD_WIDTH - DEVICE_EMESSAGE_MODULE_LEN
#define DEVICE_EMESSAGE_FID_NUMBER_LEN DEVICE_LCD_WIDTH - DEVICE_EMESSAGE_FID_LEN

namespace
{
	FlashString emessageError = FPSTR(DEVICE_EMESSAGE_ERROR);
	FlashString emessageModule = FPSTR(DEVICE_EMESSAGE_MODULE);
	FlashString emessageFID = FPSTR(DEVICE_EMESSAGE_FID);

	FlashString emessageModuleNames[(int) Device::FaultModule::_Length] PROGMEM = // 11 + \0
	{
		FPSTR("InterfaceMng"),
		FPSTR("NetworkMng  "),
		FPSTR("MapManager  "),
		FPSTR("BoardMng    "),
		FPSTR("GameAccess  "),
		FPSTR("RequestHndlr"),
		FPSTR("WebInterface")
	};
}

// Force adjustments on lcd change
static_assert(DEVICE_LCD_WIDTH == 20,
	"LCD width changed, FaultHandler needs adjustments");

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
	vvvvvvvvvvvvvvvvvvvv
   >Error: ############# <- 13 ch error message
   >#################### <- + 20 ch -> 33 ch
   >Module: ############ <- 12 ch module name
   >FailureId: ######### <- 9 digits for failure id
    ^^^^^^^^^^^^^^^^^^^^
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
			char buffer[DEVICE_LCD_WIDTH] = { };

			// print error message
			memcpy_P(buffer, emessageError, DEVICE_EMESSAGE_ERROR_LEN);
			memcpy_P(
				buffer + DEVICE_EMESSAGE_ERROR_LEN, 
				fault.text, 
				DEVICE_EMESSAGE_MESSAGE_LEN_FL);

			OutputManager::Lcd::DisplayLineType(
				0,
				buffer);

			// print remaining error message
			memcpy_P(
				buffer, 
				(const char*) fault.text + DEVICE_EMESSAGE_MESSAGE_LEN_FL, 
				DEVICE_EMESSAGE_MESSAGE_LEN);
			
			OutputManager::Lcd::DisplayLineType(
				1,
				buffer);

			// print module name
			memcpy_P(buffer, emessageModule, DEVICE_EMESSAGE_MODULE_LEN);
			memcpy_P(
				buffer + DEVICE_EMESSAGE_MODULE_LEN, 
				emessageModuleNames[(int) fault.module], 
				DEVICE_EMESSAGE_MODULE_NAME_LEN);

			OutputManager::Lcd::DisplayLineType(
				2,
				buffer);

			// print failure id
			memcpy_P(buffer, emessageFID, DEVICE_EMESSAGE_FID_LEN);
			sprintf_P(
				buffer + DEVICE_EMESSAGE_FID_LEN,
				PSTR("%09d"),
				fault.id);

			OutputManager::Lcd::DisplayLineType(
				3,
				buffer);
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

