#include "LcdAccess.h"

#include "../Communication/InterfaceManager.h"
#include "../Device/OutputManager.h"

namespace
{
	FlashString selection_common_back = FPSTR(" - Back -        ");

	struct SelectionGeneral
	{
		enum
		{
			Close,
			Settings,
			Players,
			Restart,
			Resave,
			Shutdown,
			PrintSector
		};
	};

	FlashString selection_general[] =
	{
		FPSTR(" - Close -       "),
		FPSTR("Settings         "),
		FPSTR("Players          "),
		FPSTR("Restart          "),
		FPSTR("Resave           "),
		FPSTR("Shutdown         "),
		FPSTR("PrintSector      ")
	};

	struct SelectionSpecificPlayer
	{
		enum
		{
			Back,
			ShowPid,
			Kick,
			IntType,
			PrintSector
		};
	};

	FlashString selection_specificPlayer[] =
	{
		selection_common_back,
		FPSTR("Show PlayerId    "),
		FPSTR("Kick             "),
		FPSTR("Interface Type   "),
		FPSTR("Print Sector     ")
	};
}

namespace Communication
{
	namespace LcdAccess
	{
		void GeneralMenu();

		void SelectPlayerMenu();
		void SpecificPlayerMenu(const Game::PlayerId playerId);

		void Initialize()
		{
		}

		void Uninitialize()
		{
		}

		void Process()
		{
			if (Device::OutputManager::Interact::GetChoice() ==
				Device::OutputManager::Interact::Choice::Enter)
			{
				delay(300);
				GeneralMenu();
				Game::BoardManager::ReloadLcd();
				delay(300);
			}
		}

		void GeneralMenu()
		{
			while (true)
			{
				switch (Device::OutputManager::Interact::Select(
					selection_general,
					sizeof(selection_general) / sizeof(*selection_general) ))
				{
				case SelectionGeneral::Settings:
					// ...
					
					break;
				case SelectionGeneral::Players:
					SelectPlayerMenu();
					
					break;
				case SelectionGeneral::Restart:
					ESP.restart();

					break;
				case SelectionGeneral::Resave:
					// ...
					
					break;
				case SelectionGeneral::Shutdown:
					// ...
					
					break;
				case SelectionGeneral::PrintSector:

					break;
				default:
					return;
				}
			}
		}

		void SelectPlayerMenu()
		{
			while (true)
			{
				const int selectionCount = Game::Collector::GetData()->playerCount + 1; // + back
				FlashString* selectionBuffer = new FlashString[selectionCount];

				selectionBuffer[0] = selection_common_back;

				for (int i = 1; i < selectionCount; ++i)
				{
					selectionBuffer[i] = Game::ColorToFlash(Game::SetupManager::GetData()->playerContext.data[i - 1].color);
				}

				const int result = Device::OutputManager::Interact::Select(
					selectionBuffer,
					selectionCount);
				delete[] selectionBuffer;

				if (result == 0)
				{
					return;
				}

				SpecificPlayerMenu(Game::SetupManager::GetData()->playerContext.data[result - 1].player);
			}
		}

		void SpecificPlayerMenu(const Game::PlayerId playerId)
		{
			switch (Device::OutputManager::Interact::Select(
				selection_specificPlayer,
				sizeof(selection_specificPlayer) / sizeof(*selection_specificPlayer) ))
			{
			case SelectionSpecificPlayer::ShowPid:
			{
				Device::OutputManager::Lcd::Clear();

				char lcdBuffer[DEVICE_LCD_WIDTH] = "";

				const Game::Player* const player = Game::GameManager::ReadPlayer(playerId);

				sprintf_P(
					lcdBuffer,
					(const char*)F("PlayerId: %d"),
					playerId);
				Device::OutputManager::Lcd::DisplayLineType(
					0,
					lcdBuffer);

				sprintf_P(
					lcdBuffer,
					(const char*)F("Color: %s"),
					Game::ColorToFlash(player->data->color));
				Device::OutputManager::Lcd::DisplayLineType(
					1,
					lcdBuffer);

				Device::OutputManager::Lcd::DisplayLineType(
					3,
					Device::OutputManager::Interact::GetCommonPressExit()
				);

				delay(500);

				while (Device::OutputManager::Interact::ForceGetChoice()
					!= Device::OutputManager::Interact::Choice::Enter);
			}

			break;
			case SelectionSpecificPlayer::Kick:
				Communication::InterfaceManager::RemoveInterface(playerId);

				break;
			case SelectionSpecificPlayer::IntType:

				break;
			case SelectionSpecificPlayer::PrintSector:

				break;
			default:
				return;
			}
		}
	}
}
