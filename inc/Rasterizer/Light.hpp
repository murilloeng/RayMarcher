#pragma once

//Ray Marcher
#include "RayMarcher/inc/Rasterizer/Vec3.hpp"
#include "RayMarcher/inc/Rasterizer/Color.hpp"

namespace ray_marcher
{
	namespace rasterizer
	{
		class Light
		{
		public:
			//constructor
			Light(void);

			//destructor
			~Light(void);

			//data
			Color m_ambient;
			Color m_diffuse;
			Vec3 m_direction;
		};
	}
}