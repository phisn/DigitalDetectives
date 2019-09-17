#pragma once

#pragma pack(push, 1)

namespace Game
{
	// dynamic
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

		void Begin();
		bool Restore();
	}
}

#pragma pack(pop)
