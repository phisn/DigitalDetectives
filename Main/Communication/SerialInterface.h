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
		enum CollectCommand
		{
			Join = 'j',
			Start = 's'
		};

		static void Collect();

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

			Serial.print(F("Created interface as "));
			Serial.print(id);
			Serial.print(F(" with '"));
			Serial.print(playerCharacter);
			Serial.println('\'');
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
			if (Game::Controller::GetState() != Game::GameState::Running)
			{
				return;
			}

			if (Serial.available() > 0)
			{
				delay(200); // wait for data
			}

			const int size = Serial.available();

			if (size < 2)
			{
				goto CLEAR_BUFFER;
			}

			{
				const char inputCharacter = Serial.peek();
				if (inputCharacter != playerCharacter)
				{
					if (inputCharacter >= playerCharacterCounter ||
						inputCharacter < 'a')
					{
						DEBUG_MESSAGE("Got invalid character: ");
						DEBUG_MESSAGE(inputCharacter);

						goto CLEAR_BUFFER;
					}

					DEBUG_MESSAGE("Ignoring character: ");
					DEBUG_MESSAGE(inputCharacter);

					return;
				}
				else
				{
					DEBUG_MESSAGE("Got valid character: (character, length)");
					DEBUG_MESSAGE(inputCharacter);
					DEBUG_MESSAGE(size);

					Serial.read();
				}
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

		CLEAR_BUFFER:
			while (Serial.available())
				Serial.read();
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
				target += Serial.read() - '0'; // convert char to int

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
			Serial.print(F("Collect update for "));
			Serial.println(playerCharacter);

			Serial.print(F(" - playercount: "));
			Serial.println(Game::Collector::GetData()->playerCount);
		}

		void updateRunning()
		{
			const Game::Player* const player = Game::GameManager::ReadPlayer(playerId);

			if (player == NULL)
			{
				Serial.print(F("PlayerId not found"));
			}

			Serial.print(F("Running update for "));
			Serial.println(playerCharacter);

			Serial.println(F("You: "));

			Serial.print(F(" - position: "));
			Serial.println(player->state->position);

			Serial.print(F(" - active: "));
			Serial.println(playerId == Game::GameManager::GetData()->state.activePlayer);

			Serial.print(F(" - yellow count: "));
			Serial.println(player->state->ticket.yellowTicketCount);

			Serial.print(F(" - green count: "));
			Serial.println(player->state->ticket.greenTicketCount);

			Serial.print(F(" - red count: "));
			Serial.println(player->state->ticket.redTicketCount);

			if (player->data->type == Game::PlayerData::Type::Villian)
			{
				Serial.print(F(" - black count: "));
				Serial.println(player->state->villian.ticket.blackTicketCount);

				Serial.print(F(" - double count: "));
				Serial.println(player->state->villian.ticket.doubleTicketCount);
			}
			else
			{
				Serial.print(F(" - last villian position: "));
				Serial.println(Game::GameManager::GetLastVillianPosition());
			}
		}

		void updateSetup()
		{
		}
	};
}
