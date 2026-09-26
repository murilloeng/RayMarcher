//Ray Marcher
#include "RayMarcher/inc/Rasterizer/Camera.hpp"

namespace ray_marcher
{
	namespace rasterizer
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