#pragma once

//std
#include <cstdint>

//Ray Marcher
#include "RayMarcher/inc/Interface/Plane.hpp"
#include "RayMarcher/inc/Interface/Sphere.hpp"

//defines
#define MAX_PLANES 100
#define MAX_SPHERES 100

namespace ray_marcher
{
	namespace interface
	{
		struct Scene
		{
			uint32_t m_counter_planes;
			uint32_t m_counter_spheres;
			Plane m_planes[MAX_PLANES];
			Sphere m_spheres[MAX_SPHERES];
		};
	}
}