//std
#include <cmath>
#include <algorithm>

//Ray Marcher
#include "RayMarcher/inc/CPU/Tools.hpp"

namespace ray_marcher
{
	namespace CPU
	{
		double sign(double v)
		{
			return v < 0 ? -1 : v > 0 ? +1 : 0;
		}
		double clamp(double v, double v_min, double v_max)
		{
			return fmax(fmin(v, v_max), v_min);
		}
		double clamp(uint8_t v, uint8_t v_min, uint8_t v_max)
		{
			return std::max(std::min(v, v_max), v_min);
		}
	}
}