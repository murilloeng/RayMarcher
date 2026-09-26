//std
#include <cstdlib>

//Ray Marcher
#include "RayMarcher/inc/GPU/Engine.hpp"
#include "RayMarcher/inc/CPU/Scene.hpp"
#include "RayMarcher/inc/CPU/Color.hpp"
#include "RayMarcher/inc/CPU/Plane.hpp"
#include "RayMarcher/inc/CPU/Sphere.hpp"

[[maybe_unused]] static void scene_rasterizer(void)
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
		ray_marcher::GPU::Engine().start();
	}
	catch(const std::exception& exception)
	{
		printf("%s\n", exception.what());
	}
	//return
	return EXIT_SUCCESS;
}