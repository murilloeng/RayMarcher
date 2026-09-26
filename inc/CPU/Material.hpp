#pragma once

//Ray Marcher
#include "RayMarcher/inc/CPU/Color.hpp"

namespace ray_marcher
{
	namespace CPU
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