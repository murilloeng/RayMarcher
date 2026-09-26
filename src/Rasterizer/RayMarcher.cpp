//Ray Marcher
#include "RayMarcher/inc/Rasterizer/RayMarcher.hpp"

namespace ray_marcher
{
	namespace rasterizer
	{
		//constructor
		RayMarcher::RayMarcher(void) : m_distance_min{1.00e-02}, m_distance_max{1.00e+05}, m_iterations_max{200}
		{
			return;
		}
		
		//destructor
		RayMarcher::~RayMarcher(void)
		{
			return;
		}
	}
}