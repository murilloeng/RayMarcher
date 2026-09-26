#pragma once

//Ray Marcher
#include "RayMarcher/inc/GPU/Material.hpp"

namespace ray_marcher
{
	namespace GPU
	{
		struct alignas(16) Sphere
		{
			float m_radius[4];
			float m_position[4];
			Material m_material;
		};
	}
}