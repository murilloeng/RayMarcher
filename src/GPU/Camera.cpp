//Ray Marcher
#include "RayMarcher/inc/GPU/Camera.hpp"

namespace ray_marcher
{
	namespace GPU
	{
		//constructor
		Camera::Camera(void) : m_up{0, 1, 0, 0}, m_look_at{0, 0, 0, 0}, m_position{0, 0, 1}, m_time{0}, m_focal_distance{1}
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