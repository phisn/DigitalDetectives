#pragma once

#include "../Communication/RequestHandler.h"

namespace Communication
{
	struct Interface
	{
		virtual void Process() = 0;
		virtual void Update() = 0;
	};
}
