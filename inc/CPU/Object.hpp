#pragma once

//Ray Marcher
#include "RayMarcher/inc/CPU/Vec3.hpp"
#include "RayMarcher/inc/CPU/Material.hpp"

namespace ray_marcher
{
	namespace CPU
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

			//data
			Material m_material;
		};
	}
}