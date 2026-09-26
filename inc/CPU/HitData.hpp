#pragma once

//std
#include <cstdint>

//Ray Marcher
#include "RayMarcher/inc/CPU/Vec3.hpp"
#include "RayMarcher/inc/CPU/Material.hpp"

namespace ray_marcher
{
	namespace CPU
	{
		class HitData
		{
		public:
			//constructor
			HitData(void);

			//destructor
			~HitData(void);

			//data
			Vec3 m_normal;
			Vec3 m_position;
			Material m_material;
		};
	}
}