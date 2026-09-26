#pragma once

//Ray Marcher
#include "RayMarcher/inc/Rasterizer/Color.hpp"

namespace ray_marcher
{
	namespace rasterizer
	{
		class Material
		{
		public:
			//constructor
			Material(void);

			//destructor
			~Material(void);

			//data
			Color m_color;
		};
	}
}