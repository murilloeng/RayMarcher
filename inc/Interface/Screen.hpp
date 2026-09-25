#pragma once

//std
#include <cstdint>

namespace ray_marcher
{
	namespace interface
	{
		struct alignas(16) Screen
		{
			int32_t m_width;
			int32_t m_height;
		};
	}
}