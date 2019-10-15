#pragma once

#include "../Communication/Interface.h"
#include "../Game/GameController.h"

#define COM_SERIAL_TURN_SIZE_MIN 3
#define COM_SERIAL_TURN_SIZE_MAX 5

namespace Communication
{
	struct SerialInterfaceType {};

	class SerialInterface
		:
		public Interface
	{
		static char playerCharacterCounter;
	public:
		enum Command
		{
			Turn = 't'
		};

		enum Ticket
		{
			Yellow = 'y',
			Green = 'g',
			Red = 'r',
			Black = 'b',
			Double = 'd'
		};

		void initialize(const Game::PlayerId id) override
		{
			playerCharacter = playerCharacterCounter++;
			playerId = id;
		}

		void notifyFault(const Device::Fault fault) override
		{
			Serial.println(F("Fault: "));

			Serial.print(F("Message: "));
			Serial.println(fault.text);

			Serial.print(F("Module: "));
			Serial.println(
				Device::FaultHandler::GetModuleName(fault.module)
			);

			Serial.print(F("Id: "));
			Serial.println(fault.id, 16);
		}

		void process() override
		{
			const unsigned int size = Serial.available();
	
			if (size < 2)
			{
				return;
			}

			const char inputCharacter = Serial.peek();
			if (inputCharacter != playerCharacter)
			{
				if (inputCharacter >= playerCharacterCounter ||
					inputCharacter <= 'a')
				{
					Serial.flush();
				}

				return;
			}
			else
			{
				Serial.read();
			}

			switch (Serial.read())
			{
			case Turn:
				if (size >= COM_SERIAL_TURN_SIZE_MIN ||
					size <= COM_SERIAL_TURN_SIZE_MAX)
				{
					processTurn();
				}
				else
				{
					Serial.println(F("Got invalid length for command 'Turn'"));
				}

				break;
			default:
				Serial.println(F("Invalid command"));

				break;
			}

			Serial.flush();
		}

		void update() override
		{
			switch (Game::Controller::GetState())
			{
			case Game::GameState::Collect:
				updateCollect();

				break;
			case Game::GameState::Running:
				updateRunning();

				break;
			case Game::GameState::Setup:
				updateSetup();

				break;
			}
		}

		const Game::PlayerId getPlayerId() const
		{
			return playerId;
		}

	private:
		char playerCharacter;
		Game::PlayerId playerId;

		void processTurn()
		{
			Game::Turn turn;
			turn.ticket = parseTicket();

			if (turn.ticket == Game::Ticket::_Invalid)
			{
				Serial.println(F("Got invalid ticket"));
				return;
			}

			turn.position = parseTarget();

			if (turn.position == 0)
			{
				Serial.println(F("Got invalid target"));
				return;
			}

			Game::GameManager::TurnResult result = Game::GameManager::MakeTurn(playerId, turn);
			
			if (!result.success)
			{
				Serial.println(result.message);
				return;
			}

			Serial.println(F("Turn successfully made"));
		}

		Game::Ticket parseTicket() const
		{
			switch (Serial.read())
			{
			case Yellow:
				return Game::Ticket::Yellow;

			case Green:
				return Game::Ticket::Green;

			case Red:
				return Game::Ticket::Red;

			case Black:
				return Game::Ticket::Black;

			case Double:
				return Game::Ticket::Double;

			default:
				return Game::Ticket::_Invalid;
			}
		}

		int parseTarget() const
		{
			const int targetLength = Serial.available();

			int target = 0;
			for (int i = 0;;)
			{
				target += Serial.read();

				if (++i >= targetLength)
				{
					break;
				}

				target *= 10;
			}

			if (target == 0 || target > COMMON_MAP_SIZE)
			{
				Serial.println("Invalid target");

				return 0;
			}

			return target;
		}

		void updateCollect()
		{
			Serial.print("Collect update");

			Serial.write("-> playercount: ");
			Serial.print(Game::Collector::GetData()->playerCount);
		}

		void updateRunning()
		{
		}

		void updateSetup()
		{
		}
	};
}
