#pragma once

//std
#include <cstdint>

//Ray Marcher
#include "RayMarcher/inc/Rasterizer/Vec3.hpp"
#include "RayMarcher/inc/Rasterizer/Material.hpp"

namespace ray_marcher
{
	namespace rasterizer
	{
		class HitPoint
		{
		public:
			//constructor
			HitPoint(void);

			//destructor
			~HitPoint(void);

			//data
			bool m_status;
			Vec3 m_normal;
			Vec3 m_position;
			Material m_material;
		};
	}
}