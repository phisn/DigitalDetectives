#pragma once

#pragma pack(push, 1)

namespace Game
{
	struct CollectData
	{
		struct StaticContext
		{
			unsigned char playerCount : 3;

		} context;
	};

	namespace Collector
	{
		struct DynamicContext
		{
		};

		static DynamicContext getDynamicContext()
		{
			return { };
		}

		void Create();
		bool Process();
		void Restore();
	}
}

#pragma pack(pop)
