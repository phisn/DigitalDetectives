#include "Device/DeviceManager.h"

void setup()
{
	Device::Manager::Initialize();
}

void loop()
{
	Device::Manager::Process();
}

