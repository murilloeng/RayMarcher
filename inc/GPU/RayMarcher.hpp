#pragma once

//std
#include <cstdint>

namespace ray_marcher
{
	namespace GPU
	{
		struct alignas(16) RayMarcher
		{
			uint32_t m_iteration_max = 1000;
			float m_distance_min = 1.00e-02f;
			float m_distance_max = 1.00e+05f;
		};
	}
}