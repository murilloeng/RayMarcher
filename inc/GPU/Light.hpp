#pragma once

//std
#include <cstdint>

//Ray Marcher
#include "RayMarcher/inc/GPU/Color.hpp"

namespace ray_marcher
{
	namespace GPU
	{
		struct alignas(16) Light
		{
			//constructor
			Light(void);

			//destructor
			~Light(void);

			//data
			Color m_ambient;
			Color m_diffuse;
			float m_direction[4];
		};
	}
}