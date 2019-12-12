#include "WebsiteConstructor.h"

namespace
{
	FlashString webparts[(int) Communication::Webpart::_Length] =
	{
		FPSTR(""),
		FPSTR(""),
	};

	size_t webpartsSize[(int)Communication::Webpart::_Length] =
	{
		0,
		0
	};
}

namespace Communication
{
	namespace WebsiteConstructor
	{
		size_t CalculateSize(Webpart* const website);
		char* Construct(Webpart* website)
		{
			char* const buffer = (char*) Device::MemoryManager::AllocateDynamic(CalculateSize(website));
			size_t offset = 0;

			while (true)
			{
				const size_t webpartSize = webpartsSize[(int) *website];

				memcpy_P(buffer + offset,
					(const void*) webparts[(int) *website],
					webpartSize);
				offset += webpartSize;

				if (*website == Webpart::End)
				{
					break;
				}

				++website;
			}

			return buffer;
		}

		size_t CalculateSize(Webpart* website)
		{
			size_t size = 0;

			while (true)
			{
				size += webpartsSize[(int) *website];

				if (*website == Webpart::End)
				{
					break;
				}

				++website;
			}

			return size;
		}
	}
}