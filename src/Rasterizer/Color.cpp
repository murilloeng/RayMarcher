//Ray Marcher
#include "RayMarcher/inc/Rasterizer/Color.hpp"

namespace ray_marcher
{
	namespace rasterizer
	{
		//constructor
		Color::Color(void) : m_channels{0, 0, 0}
		{
			return;
		}
		Color::Color(double gray) : m_channels{gray, gray, gray}
		{
			return;
		}
		Color::Color(double r, double g, double b) : m_channels{r, g, b}
		{
			return;
		}
		
		//destructor
		Color::~Color(void)
		{
			return;
		}

		//apply
		void Color::apply(uint8_t* buffer) const
		{
			buffer[0] = uint8_t(255 * m_channels[0]);
			buffer[1] = uint8_t(255 * m_channels[1]);
			buffer[2] = uint8_t(255 * m_channels[2]);
		}

		//operators
		Color& Color::operator*=(double s)
		{
			m_channels[0] *= s;
			m_channels[1] *= s;
			m_channels[2] *= s;
			return *this;
		}
		Color& Color::operator/=(double s)
		{
			m_channels[0] /= s;
			m_channels[1] /= s;
			m_channels[2] /= s;
			return *this;
		}
		Color& Color::operator+=(const Color& color)
		{
			m_channels[0] += color.m_channels[0];
			m_channels[1] += color.m_channels[1];
			m_channels[2] += color.m_channels[2];
			return *this;
		}
		Color& Color::operator-=(const Color& color)
		{
			m_channels[0] -= color.m_channels[0];
			m_channels[1] -= color.m_channels[1];
			m_channels[2] -= color.m_channels[2];
			return *this;
		}

		Color Color::operator/(double s) const
		{
			return Color(*this) /= s;
		}
		Color Color::operator+(const Color& color) const
		{
			return Color(*this) += color;
		}
		Color Color::operator-(const Color& color) const
		{
			return Color(*this) -= color;
		}

		Color operator*(double s, const Color& color)
		{
			return Color(color) *= s;
		}
	}
}