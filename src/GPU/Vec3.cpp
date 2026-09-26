//std
#include <cmath>

//Ray Marcher
#include "RayMarcher/inc/GPU/Vec3.hpp"

namespace ray_marcher
{
	namespace GPU
	{
		//constructor
		Vec3::Vec3(void) : m_data{0, 0, 0}
		{
			return;
		}
		Vec3::Vec3(double x1, double x2, double x3) : m_data{x1, x2, x3}
		{
			return;
		}
		
		//destructor
		Vec3::~Vec3(void)
		{
			return;
		}

		//operators
		Vec3& Vec3::operator*=(double s)
		{
			m_data[0] *= s;
			m_data[1] *= s;
			m_data[2] *= s;
			return *this;
		}
		Vec3& Vec3::operator/=(double s)
		{
			m_data[0] /= s;
			m_data[1] /= s;
			m_data[2] /= s;
			return *this;
		}
		Vec3& Vec3::operator+=(const Vec3& vector)
		{
			m_data[0] += vector.m_data[0];
			m_data[1] += vector.m_data[1];
			m_data[2] += vector.m_data[2];
			return *this;
		}
		Vec3& Vec3::operator-=(const Vec3& vector)
		{
			m_data[0] -= vector.m_data[0];
			m_data[1] -= vector.m_data[1];
			m_data[2] -= vector.m_data[2];
			return *this;
		}

		Vec3 Vec3::operator+(void) const
		{
			return *this;
		}
		Vec3 Vec3::operator-(void) const
		{
			return Vec3(*this) *= -1;
		}
		Vec3 Vec3::operator+(const Vec3& vector) const
		{
			return Vec3(*this) += vector;
		}
		Vec3 Vec3::operator-(const Vec3& vector) const
		{
			return Vec3(*this) -= vector;
		}

		double& Vec3::operator[](uint32_t index)
		{
			return m_data[index];
		}
		const double& Vec3::operator[](uint32_t index) const
		{
			return m_data[index];
		}

		Vec3 operator*(double s, const Vec3& vector)
		{
			return Vec3(vector) *= s;
		}

		//linear
		Vec3 Vec3::unit(void) const
		{
			return Vec3(*this) /= norm();
		}
		Vec3 Vec3::cross(const Vec3& vector) const
		{
			return Vec3(
				m_data[1] * vector.m_data[2] - m_data[2] * vector.m_data[1],
				m_data[2] * vector.m_data[0] - m_data[0] * vector.m_data[2],
				m_data[0] * vector.m_data[1] - m_data[1] * vector.m_data[0]
			);
		}

		double Vec3::norm(void) const
		{
			return sqrt(inner(*this));
		}
		double Vec3::inner(const Vec3& vector) const
		{
			return m_data[0] * vector.m_data[0] + m_data[1] * vector.m_data[1] + m_data[2] * vector.m_data[2];
		}
	}
}