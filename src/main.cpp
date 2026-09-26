//std
#include <cmath>
#include <cstdlib>

//Ray Marcher
#include "RayMarcher/inc/GPU/Engine.hpp"
#include "RayMarcher/inc/CPU/Scene.hpp"
#include "RayMarcher/inc/CPU/Color.hpp"
#include "RayMarcher/inc/CPU/Plane.hpp"
#include "RayMarcher/inc/CPU/Sphere.hpp"

class MyEngine : public ray_marcher::GPU::Engine
{
	void update_scene(void) override
	{
		const float t = m_camera.m_time;
		m_scene.m_spheres[1].m_center[0] = -0.3 * cosf(2 * M_PI * t);
		m_scene.m_spheres[1].m_center[2] = -0.3 * sinf(2 * M_PI * t);
		m_scene.m_spheres[2].m_center[0] = +0.3 * cosf(2 * M_PI * t);
		m_scene.m_spheres[2].m_center[2] = +0.3 * sinf(2 * M_PI * t);
	}
};

[[maybe_unused]] static void scene_GPU(void)
{
	//data
	MyEngine engine;
	//planes
	engine.m_scene.m_counter[0] = 1;
	engine.m_scene.m_planes[0].m_point[0] = 0;
	engine.m_scene.m_planes[0].m_point[1] = -0.2;
	engine.m_scene.m_planes[0].m_point[2] = 0;
	engine.m_scene.m_planes[0].m_normal[0] = 0;
	engine.m_scene.m_planes[0].m_normal[1] = 1;
	engine.m_scene.m_planes[0].m_normal[2] = 0;
	engine.m_scene.m_planes[0].m_material.m_color[0] = 0.8;
	engine.m_scene.m_planes[0].m_material.m_color[1] = 0.8;
	engine.m_scene.m_planes[0].m_material.m_color[2] = 0.8;
	//spheres
	engine.m_scene.m_counter[1] = 3;
	engine.m_scene.m_spheres[0].m_radius = 0.1;
	engine.m_scene.m_spheres[1].m_radius = 0.1;
	engine.m_scene.m_spheres[2].m_radius = 0.1;
	engine.m_scene.m_spheres[0].m_center[0] = 0;
	engine.m_scene.m_spheres[0].m_center[1] = 0;
	engine.m_scene.m_spheres[0].m_center[2] = 0;
	engine.m_scene.m_spheres[1].m_center[0] = -0.3;
	engine.m_scene.m_spheres[1].m_center[1] = 0;
	engine.m_scene.m_spheres[1].m_center[2] = 0;
	engine.m_scene.m_spheres[2].m_center[0] = +0.3;
	engine.m_scene.m_spheres[2].m_center[1] = 0;
	engine.m_scene.m_spheres[2].m_center[2] = 0;
	engine.m_scene.m_spheres[0].m_material.m_color[0] = 1;
	engine.m_scene.m_spheres[0].m_material.m_color[1] = 0;
	engine.m_scene.m_spheres[0].m_material.m_color[2] = 0;
	engine.m_scene.m_spheres[1].m_material.m_color[0] = 0;
	engine.m_scene.m_spheres[1].m_material.m_color[1] = 1;
	engine.m_scene.m_spheres[1].m_material.m_color[2] = 0;
	engine.m_scene.m_spheres[2].m_material.m_color[0] = 0;
	engine.m_scene.m_spheres[2].m_material.m_color[1] = 0;
	engine.m_scene.m_spheres[2].m_material.m_color[2] = 1;
	//transfer
	engine.m_ubo->transfer(0, sizeof(ray_marcher::GPU::Scene), &engine.m_scene);
	//start
	engine.start();
}
[[maybe_unused]] static void scene_CPU(void)
{
	//data
	ray_marcher::CPU::Scene scene;
	ray_marcher::CPU::Plane* plane = new ray_marcher::CPU::Plane;
	ray_marcher::CPU::Sphere* spheres[] = {new ray_marcher::CPU::Sphere, new ray_marcher::CPU::Sphere, new ray_marcher::CPU::Sphere};
	//plane
	plane->m_material.m_color = 0.9;
	plane->m_point = {+0.0, -0.2, +0.0};
	plane->m_normal = {+0.0, +1.0, +0.0};
	//sphere
	spheres[0]->m_radius = 0.1;
	spheres[1]->m_radius = 0.1;
	spheres[2]->m_radius = 0.1;
	spheres[0]->m_center = {-0.4, 0, 0};
	spheres[1]->m_center = {+0.0, 0, 0};
	spheres[2]->m_center = {+0.4, 0, 0};
	spheres[0]->m_material.m_color = {1, 0, 0};
	spheres[1]->m_material.m_color = {1, 0, 0};
	spheres[2]->m_material.m_color = {1, 0, 0};
	//objects
	scene.m_objects.push_back(plane);
	scene.m_objects.push_back(spheres[0]);
	scene.m_objects.push_back(spheres[1]);
	scene.m_objects.push_back(spheres[2]);
	//scene
	scene.setup();
	scene.draw();
	scene.write_image("test.ppm", true);
}

int main(void)
{
	try
	{
		scene_GPU();
	}
	catch(const std::exception& exception)
	{
		printf("%s\n", exception.what());
	}
	//return
	return EXIT_SUCCESS;
}