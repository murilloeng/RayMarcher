//Ray Marcher
#include "RayMarcher/inc/CPU/Sphere.hpp"

namespace ray_marcher
{
	namespace CPU
	{
		//constructor
		Sphere::Sphere(void) : m_center{0, 0, 0}, m_radius{0}
		{
			return;
		}
		Sphere::Sphere(Vec3 center, double radius) : m_center{center}, m_radius{radius}
		{
			return;
		}

		//destructor
		Sphere::~Sphere(void)
		{
			return;
		}

		//sdf
		double Sphere::sdf(const Vec3& point) const
		{
			return (point - m_center).norm() - m_radius;
		}
		Vec3 Sphere::normal(const Vec3& point) const
		{
			return (point - m_center).unit();
		}
	}
}