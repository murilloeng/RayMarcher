#version 460 core

//data
out vec4 fragment;

//defines
#define MAX_PLANES 100
#define MAX_SPHERES 100

//structures
struct Screen
{
	int m_width;
	int m_height;
};
struct Camera
{
	vec3 m_up;
	vec3 m_look_at;
	vec3 m_position;
	float m_time, m_focal_distance;
};
struct RayMarcher
{
	uint m_iteration_max;
	float m_distance_min;
	float m_distance_max;
};
struct Material
{
	vec3 m_color;
};
struct HitData
{
	vec3 m_normal;
	vec3 m_position;
	Material m_material;
};
struct Plane
{
	vec3 m_point;
	vec3 m_normal;
	Material m_material;
};
struct Sphere
{
	vec3 m_center;
	float m_radius;
	Material m_material;
};
struct Light
{
	vec3 m_ambient;
	vec3 m_diffuse;
	vec3 m_direction;
};
struct Scene
{
	Light m_light;
	uint m_counter_planes;
	uint m_counter_spheres;
	Plane[MAX_PLANES] m_planes;
	Sphere[MAX_SPHERES] m_spheres;
};

//uniforms
layout(std140, binding = 0) uniform uniform_data
{
	Scene scene;
	Screen screen;
	Camera camera;
	RayMarcher ray_marcher;
};

//SDFs
float sdPlane(vec3 p, Plane plane)
{
	return dot(p - plane.m_point, plane.m_normal);
}
float sdSphere(vec3 p, Sphere sphere)
{
	return length(p - sphere.m_center) - sphere.m_radius;
}

//Ray Marching
bool ray_march(vec3 ray_position, vec3 ray_direction, out HitData hit_data)
{
	float ray_length = 0;
	for(uint iteration = 0; iteration < ray_marcher.m_iteration_max; iteration++)
	{
		float d = ray_marcher.m_distance_max;
		for(uint plane_id = 0; plane_id < scene.m_counter_planes; plane_id++)
		{
			d = min(d, sdPlane(ray_position, scene.m_planes[plane_id]));
			if(d < ray_marcher.m_distance_min)
			{
				hit_data.m_position = ray_position;
				hit_data.m_normal = scene.m_planes[plane_id].m_normal;
				hit_data.m_material = scene.m_planes[plane_id].m_material;
				return true;
			}
		}
		for(uint sphere_id = 0; sphere_id < scene.m_counter_planes; sphere_id++)
		{
			d = min(d, sdSphere(ray_position, scene.m_spheres[sphere_id]));
			if(d < ray_marcher.m_distance_min)
			{
				hit_data.m_position = ray_position;
				hit_data.m_material = scene.m_planes[sphere_id].m_material;
				hit_data.m_normal = normalize(ray_position - scene.m_spheres[sphere_id].m_center);
				return true;
			}
		}
		ray_length += d;
		ray_position += d * ray_direction;
		if(ray_length > ray_marcher.m_distance_max) return false;
	}
	return false;
}

//main
void main(void)
{
	//data
	const float w = screen.m_width;
	const float h = screen.m_height;
	const float u = w / min(w, h) * (2 * gl_FragCoord.x / w - 1);
	const float v = h / min(w, h) * (2 * gl_FragCoord.y / h - 1);
	//camera
	const vec3 t2 = camera.m_up;
	const vec3 t3 = normalize(camera.m_position - camera.m_look_at);
	const vec3 t1 = cross(t2, t3);
	//background
	fragment = vec4((3 - v) / 4, (3 - v) / 4, 1, 1);
	//fragment
	// HitData hit_data;
	// if(ray_march(camera.m_position, normalize(u * t1 + v * t2 - camera.m_focal_distance * t3), hit_data))
	// {
	// 	fragment.rgb = hit_data.m_material.m_color;
	// }
}