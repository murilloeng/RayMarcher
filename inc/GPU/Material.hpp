#pragma once

namespace ray_marcher
{
	namespace GPU
	{
		struct alignas(16) Material
		{
			float m_color[4];
		};
	}
}