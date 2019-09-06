#include "FaultHandler.h"

// minus null byte
#define DEVICE_EMESSAGE_ERROR_LEN (sizeof(DEVICE_EMESSAGE_ERROR) - 1)
#define DEVICE_EMESSAGE_MODULE_LEN (sizeof(DEVICE_EMESSAGE_MODULE) - 1)
#define DEVICE_EMESSAGE_FID_LEN (sizeof(DEVICE_EMESSAGE_FID) - 1)

#define DEVICE_EMESSAGE_MESSAGE_LEN_FL DEVICE_LCD_WIDTH - DEVICE_EMESSAGE_ERROR_LEN
#define DEVICE_EMESSAGE_MODULE_NAME_LEN DEVICE_LCD_WIDTH - DEVICE_EMESSAGE_MODULE_LEN
#define DEVICE_EMESSAGE_FID_NUMBER_LEN DEVICE_LCD_WIDTH - DEVICE_EMESSAGE_FID_LEN

namespace
{
	FlashString emessageError = FPSTR(DEVICE_EMESSAGE_ERROR);
	FlashString emessageErrorNonFatal FPSTR(DEVICE_EMESSAGE_ERROR_NONFATAL);
	FlashString emessageModule = FPSTR(DEVICE_EMESSAGE_MODULE);
	FlashString emessageFID = FPSTR(DEVICE_EMESSAGE_FID);

	FlashString emessageModuleNames[(int) Device::FaultModule::_Length] PROGMEM = // 11 + \0
	{
		FPSTR("FaultHandler\0"),
		FPSTR("NetworkMng  \0"),
		FPSTR("MapManager  \0"),
		FPSTR("BoardManager\0"),
		FPSTR("GameManager \0"),
		FPSTR("GameAccess  \0"),
		FPSTR("InterfaceMng\0"),
		FPSTR("RequestHndlr\0"),
		FPSTR("WebInterface\0")
	};

	FlashString fault_intmg_null = DEVICE_FAULT_MESSAGE("IntMg callback was null       ");
	FlashString fault_low_memory = DEVICE_FAULT_MESSAGE("Device has low memory         ");
}

// prevent accidential change of nonfatal
static_assert(sizeof(DEVICE_EMESSAGE_ERROR) == sizeof(DEVICE_EMESSAGE_ERROR_NONFATAL),
	"Replacement 'non-fatal' must have the same size as the normal error");

// Force adjustments on lcd change
static_assert(DEVICE_LCD_WIDTH == 20,
	"LCD width changed, FaultHandler needs adjustments");

// ################### <- 20
// ########            <- 9
//         ########### <- 11 
// Module: InterfaceMg   

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
		void DisplayFaultMessage(const Fault fault, const bool fatal);
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

		void Report()
		{
		}

		void Handle(const Fault fault, const bool fatal)
		{
			/*
			
			if (interfaceNotifierCallback == NULL)
			{
				Handle(
				{
					FaultModule::FaultHandler,
					(FailureId) FID::INC_NULL,
					fault_intmg_null
				});
			/}
			
			*/

			DisplayFaultMessage(fault, fatal);

			if (fatal)
			{
				if ()
				interfaceNotifierCallback(fault);
				HandleModuleFault(fault);
			}
		}

		void ValidateDeviceState()
		{
			// ex. check if device memory overflows

			if (ESP.getFreeHeap() < DEVICE_MIN_REMAIN_MEMORY || 
				ESP.getFreeContStack() < DEVICE_MIN_REMAIN_MEMORY)
			{
				Handle(
				{
					FaultModule::FaultHandler,
					(FailureId)FID::LOW_MEMORY,
					fault_low_memory
				});
			}

			/*
				if (ESP.getHeapFragmentation() > 90)
				{
					// high frag
				}
			*/

			/*
				ESP.getFreeHeap();
				ESP.getFreeContStack();

				// ESP.getFreeSketchSpace();
				ESP.getHeapFragmentation();
				ESP.getHeapStats();
				ESP.getMaxFreeBlockSize();
			*/
		}

		void DisplayFaultMessage(const Fault fault, const bool fatal)
		{
			OutputManager::Lcd::Clear();
			char buffer[DEVICE_LCD_WIDTH + 1] = { };

			// print error message
			memcpy_P(
				buffer,  
				fatal ? emessageError : emessageErrorNonFatal,
				DEVICE_EMESSAGE_ERROR_LEN);
			memcpy_P(
				buffer + DEVICE_EMESSAGE_ERROR_LEN, 
				(const char*) fault.text, 
				DEVICE_EMESSAGE_MESSAGE_LEN_FL);

			OutputManager::Lcd::DisplayLineType(
				0,
				buffer);

			// memset(buffer, 0, DEVICE_LCD_WIDTH + 1);

			// print remaining error message
			// ignore space on next line
			const bool offset = pgm_read_byte((const char*) fault.text + DEVICE_EMESSAGE_MESSAGE_LEN_FL) == ' ';
			memcpy_P(
				buffer, 
				(const char*) fault.text + DEVICE_EMESSAGE_MESSAGE_LEN_FL + offset,
				DEVICE_LCD_WIDTH - offset);

			OutputManager::Lcd::DisplayLineType(
				1,
				buffer);

			// memset(buffer, 0, DEVICE_LCD_WIDTH + 1);

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

