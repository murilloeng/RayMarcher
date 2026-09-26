//Ray Marcher
#include "RayMarcher/inc/CPU/Plane.hpp"

namespace ray_marcher
{
	namespace CPU
	{
		//constructor
		Plane::Plane(void) : m_point{0, 0, 0}, m_normal{0, 0, 0}
		{
			return;
		}
		Plane::Plane(Vec3 point, Vec3 normal) : m_point{point}, m_normal{normal}
		{
			return;
		}

		//destructor
		Plane::~Plane(void)
		{
			return;
		}

		//sdf
		double Plane::sdf(const Vec3& point) const
		{
			return (point - m_point).inner(m_normal);
		}
		Vec3 Plane::normal(const Vec3& point) const
		{
			return m_normal;
		}
	}
}