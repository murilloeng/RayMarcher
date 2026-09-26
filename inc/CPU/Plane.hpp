#pragma once

//Ray Marcher
#include "RayMarcher/inc/CPU/Object.hpp"

namespace ray_marcher
{
	namespace CPU
	{
		class Plane : public Object
		{
		public:
			//constructor
			Plane(void);
			Plane(Vec3, Vec3);

			//destructor
			~Plane(void);

			//sdf
			double sdf(const Vec3&) const override;
			Vec3 normal(const Vec3&) const override;

			//data
			Vec3 m_point;
			Vec3 m_normal;
		};
	}
}