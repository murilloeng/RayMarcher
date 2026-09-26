#pragma once

//Ray Marcher
#include "RayMarcher/inc/Rasterizer/Object.hpp"

namespace ray_marcher
{
	namespace rasterizer
	{
		class Sphere : public Object
		{
		public:
			//constructor
			Sphere(void);
			Sphere(Vec3, double);

			//destructor
			~Sphere(void);

			//sdf
			double sdf(const Vec3&) const override;
			Vec3 normal(const Vec3&) const override;

			//data
			Vec3 m_center;
			double m_radius;
		};
	}
}