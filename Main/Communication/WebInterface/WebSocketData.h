#pragma once

namespace Communication
{
	namespace WebSocketData
	{
		struct Type 
		{
			enum : unsigned char
			{
				Invalid,
				Collect = 1,
				Setup = 2,
				Running = 3
			} type;
		};

		struct CollectData
		{
			Type type{ Type::Collect }; // 1 byte
			int8_t playerCount;			// 1 byte
		};

		struct SetupData
		{
			Type type{ Type::Setup };
		};

		struct RunningData
		{
			Type type{ Type::Running };
		};

		// ensure size to prevent breaking js
		static_assert(sizeof(CollectData) == 2, "Invalid CollectData size");
	}
}