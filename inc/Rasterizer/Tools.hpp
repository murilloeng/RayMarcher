#pragma once

//std
#include <cstdint>

namespace ray_marcher
{
	namespace rasterizer
	{
		double sign(double);
		double clamp(double, double, double);
		double clamp(uint8_t, uint8_t, uint8_t);
	}
}