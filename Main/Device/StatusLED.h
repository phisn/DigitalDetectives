#pragma once

#pragma pack(push, 1)

#include "../Common/Common.h"

namespace Device
{
	struct RGB
	{
		unsigned char r, g, b;
	};

	namespace StatusLED
	{
		void Initialize();
		void Unintialize();

		void Show(const RGB color);
	}
}

#pragma push(pop)
