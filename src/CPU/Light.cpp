//Ray Marcher
#include "RayMarcher/inc/CPU/Light.hpp"

namespace ray_marcher
{
	namespace CPU
	{
		//constructor
		Light::Light(void) : m_ambient{0.2}, m_diffuse{1.0}, m_direction{0, -1, 0}
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