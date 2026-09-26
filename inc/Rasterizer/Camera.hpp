#pragma once

//Ray Marcher
#include "RayMarcher/inc/Rasterizer/Vec3.hpp"

namespace ray_marcher
{
	namespace rasterizer
	{
		class Camera
		{
		public:
			//constructor
			Camera(void);

			//destructor
			~Camera(void);

			//data
			Vec3 m_up;
			Vec3 m_lookat;
			Vec3 m_position;
			double m_focal_distance;
		};
	}
}