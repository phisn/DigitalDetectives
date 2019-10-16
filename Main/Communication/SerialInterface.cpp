#include "SerialInterface.h"
#include "../Communication/InterfaceManager.h"

char Communication::SerialInterface::playerCharacterCounter = 'a';

void Communication::SerialInterface::Collect()
{
	const int size = Serial.available();

	if (size != 1)
	{
		while (Serial.available())
			Serial.read();

		return;
	}

	switch (Serial.read())
	{
	case Join:
		Serial.println("Creating interface");
		::Communication::InterfaceManager::CreateInterface<SerialInterfaceType>();

		break;
	case Start:
		Serial.println("Starting game");
		::Game::Controller::RequestFinish();

		break;
	}
}
