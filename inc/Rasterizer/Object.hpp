#pragma once

//Ray Marcher
#include "RayMarcher/inc/Rasterizer/Vec3.hpp"

namespace ray_marcher
{
	namespace rasterizer
	{
		class Object
		{
		public:
			//constructor
			Object(void);

			//destructor
			virtual ~Object(void);

			//sdf
			virtual double sdf(const Vec3&) const = 0;
			virtual Vec3 normal(const Vec3&) const = 0;
		};
	}
}