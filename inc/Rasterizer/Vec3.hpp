#pragma once

//std
#include <cstdint>

namespace ray_marcher
{
	namespace rasterizer
	{
		class Vec3
		{
		public:
			//constructor
			Vec3(void);
			Vec3(double, double, double);

			//destructor
			~Vec3(void);

			//operators
			Vec3& operator*=(double);
			Vec3& operator/=(double);
			Vec3& operator+=(const Vec3&);
			Vec3& operator-=(const Vec3&);
			
			Vec3 operator+(const Vec3&) const;
			Vec3 operator-(const Vec3&) const;

			double& operator[](uint32_t);
			const double& operator[](uint32_t) const;

			friend Vec3 operator*(double, const Vec3&);

			//linear
			Vec3 unit(void) const;
			Vec3 cross(const Vec3&) const;

			double norm(void) const;
			double inner(const Vec3&) const;

			//data
			double m_data[3];
		};
	}
}