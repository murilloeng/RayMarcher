#pragma once

namespace ray_marcher
{
	namespace interface
	{
		struct alignas(16) Camera
		{
			float m_up[4];
			float m_look_at[4];
			float m_position[3];
			float m_time, m_focal_distance;
		};
	}
}