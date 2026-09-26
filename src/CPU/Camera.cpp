//Ray Marcher
#include "RayMarcher/inc/CPU/Camera.hpp"

namespace ray_marcher
{
	namespace CPU
	{
		//constructor
		Camera::Camera(void) : m_up{0, 1, 0}, m_lookat{0, 0, 0}, m_position{0, 0, 1}, m_focal_distance{1}
		{
			return;
		}
		
		//destructor
		Camera::~Camera(void)
		{
			return;
		}
	}
}