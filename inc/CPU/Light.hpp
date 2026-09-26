#pragma once

//Ray Marcher
#include "RayMarcher/inc/CPU/Vec3.hpp"
#include "RayMarcher/inc/CPU/Color.hpp"

namespace ray_marcher
{
	namespace CPU
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