#pragma once

#include <WString.h>

namespace FaultHandler
{
	void RebootDevice(PGM_P reason);
	void Log(PGM_P message);
	void LogVisual(PGM_P message);
}
