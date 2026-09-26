#pragma once

//std
#include <cstdint>

namespace ray_marcher
{
	namespace rasterizer
	{
		class RayMarcher
		{
		public:
			//constructor
			RayMarcher(void);

			//destructor
			~RayMarcher(void);

			//data
			double m_distance_min;
			double m_distance_max;
			uint32_t m_iterations_max;
		};
	}
}