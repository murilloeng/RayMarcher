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
struct HitPoint
{
	bool m_status;
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
	vec3 m_direction;
};
struct Scene
{
	uint m_counter_planes;
	uint m_counter_spheres;
	Plane[MAX_PLANES] m_planes;
	Sphere[MAX_SPHERES] m_spheres;
};

//uniforms
layout(std140, binding = 0) uniform uniform_data
{
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

//main
void main(void)
{
	//data
	Light light;
	HitPoint hit_point;
	const float w = screen.m_width;
	const float h = screen.m_height;
	const float u = w / min(w, h) * (2 * gl_FragCoord.x / w - 1);
	const float v = h / min(w, h) * (2 * gl_FragCoord.y / h - 1);
	//scene
	Scene scene;
	scene.m_counter_spheres = 1;
	scene.m_spheres[0].m_radius = 0.5;
	scene.m_spheres[0].m_center = vec3(0, 0, 0);
	scene.m_spheres[0].m_material.m_color = vec3(0, 1, 0);
	//background
	fragment = vec4((3 - v) / 4, (3 - v) / 4, 1, 1);
	//fragment
	hit_point.m_status = false;
	vec3 ray_position = vec3(0, 0, 1);
	light.m_direction = vec3(cos(camera.m_time), 0, sin(camera.m_time));
	const vec3 ray_direction = normalize(vec3(u, v, 0) - ray_position);
	for(uint iteration = 0; iteration < ray_marcher.m_iteration_max && !hit_point.m_status; iteration++)
	{
		float d = ray_marcher.m_distance_max;
		for(uint sphere_id = 0; sphere_id < scene.m_counter_spheres; sphere_id++)
		{
			d = min(d, sdSphere(ray_position, scene.m_spheres[sphere_id]));
			if(d < ray_marcher.m_distance_min)
			{
				hit_point.m_status = true;
				hit_point.m_normal = normalize(ray_position - scene.m_spheres[sphere_id].m_center);
				hit_point.m_material = scene.m_spheres[sphere_id].m_material;
			}
		}
		ray_position += d * ray_direction;
		if(d > ray_marcher.m_distance_max) break;
	}
	if(hit_point.m_status) fragment.rgb = dot(hit_point.m_normal, -light.m_direction) * hit_point.m_material.m_color;
}