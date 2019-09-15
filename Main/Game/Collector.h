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
		static struct DynamicContext
		{


		} getDynamicContext()
		{
			return { };
		}

		void Begin();
		bool Restore();
	}
}

#pragma pack(pop)
