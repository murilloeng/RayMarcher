//std
#include <cstdint>

//defines
#define MAX_PLANES 100
#define MAX_SPHERES 100

namespace ray_marcher
{
	namespace GPU
	{
		//structures
		struct alignas(16) Screen
		{
			int m_width;
			int m_height;
		};
		struct alignas(16) Camera
		{
			float m_up[4] = {0, 1, 0, 0};
			float m_look_at[4] = {0, 0, 0, 0};
			float m_position[3] = {0, 0, 1};
			float m_time = 0, m_focal_distance = 1;
		};
		struct alignas(16) RayMarcher
		{
			float m_distance_min = 1.00e-02f;
			float m_distance_max = 1.00e+05f;
			uint32_t m_iteration_max = 200;
		};
		struct alignas(16) Material
		{
			float m_color[3] = {0, 0, 0};
		};
		struct alignas(16) Plane
		{
			float m_point[4] = {0, 0, 0};
			float m_normal[4] = {0, 1, 0};
			Material m_material;
		};
		struct alignas(16) Sphere
		{
			float m_center[3] = {0, 0, 0};
			float m_radius = 1.00e+00f;
			Material m_material;
		};
		struct alignas(16) Light
		{
			float m_ambient[4] = {0.1, 0.1, 0.1, 0};
			float m_diffuse[4] = {1.0, 1.0, 1.0, 1};
			float m_direction[4] = {0, -1, 0, 0};
		};
		struct alignas(16) Scene
		{
			Light m_light;
			uint32_t m_counter[4] = {0, 0, 0, 0};
			Plane m_planes[MAX_PLANES];
			Sphere m_spheres[MAX_SPHERES];
		};
	}
}