#pragma once

//std
#include <cstdint>

//Ray Marcher
#include "RayMarcher/inc/GPU/Light.hpp"
#include "RayMarcher/inc/GPU/Plane.hpp"
#include "RayMarcher/inc/GPU/Sphere.hpp"

//defines
#define MAX_PLANES 100
#define MAX_SPHERES 100

namespace ray_marcher
{
	namespace GPU
	{
		struct alignas(16) Scene
		{
			Light m_light;
			uint32_t m_counter_planes;
			uint32_t m_counter_spheres;
			Plane m_planes[MAX_PLANES];
			Sphere m_spheres[MAX_SPHERES];
		};
	}
}