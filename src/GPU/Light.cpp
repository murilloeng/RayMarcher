//Ray Marcher
#include "RayMarcher/inc/GPU/Light.hpp"

namespace ray_marcher
{
	namespace GPU
	{
		//constructor
		Light::Light(void) : m_ambient{0.1}
		{
			return;
		}

		//destructor
		Light::~Light(void)
		{
			return;
		}
	}
}