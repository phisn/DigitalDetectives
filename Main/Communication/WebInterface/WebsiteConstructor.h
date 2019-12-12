#pragma once

namespace Communication
{
	enum class Webpart
	{
		Begin,


		
		End,
		_Length
	};

	namespace WebsiteConstructor
	{
		char* Construct(Webpart* const website);
	}
}
