#pragma once

//std
#include <cstdint>

namespace ray_marcher
{
	namespace rasterizer
	{
		class Color
		{
		public:
			//constructor
			Color(void);
			Color(double);
			Color(double, double, double);

			//destructor
			~Color(void);

			//apply
			void apply(uint8_t*) const;

			//operators
			Color& operator*=(double);
			Color& operator/=(double);
			Color& operator+=(const Color&);
			Color& operator-=(const Color&);

			Color operator/(double) const;
			Color operator+(const Color&) const;
			Color operator-(const Color&) const;

			friend Color operator*(double, const Color&);

			//data
			double m_channels[3];
		};
	}
}