//std
#include <cstdlib>

//Ray Marcher
#include "RayMarcher/inc/Interface/Engine.hpp"
#include "RayMarcher/inc/Rasterizer/Scene.hpp"
#include "RayMarcher/inc/Rasterizer/Color.hpp"
#include "RayMarcher/inc/Rasterizer/Plane.hpp"
#include "RayMarcher/inc/Rasterizer/Sphere.hpp"

int main(void)
{
	try
	{
		//data
		ray_marcher::rasterizer::Scene scene;
		ray_marcher::rasterizer::Plane* plane = new ray_marcher::rasterizer::Plane;
		ray_marcher::rasterizer::Sphere* sphere = new ray_marcher::rasterizer::Sphere;
		//plane
		plane->m_point = {0, -1, 0};
		plane->m_normal = {0, +1, 0};
		plane->m_material.m_color = {1, 0, 0};
		//sphere
		sphere->m_radius = 0.1;
		sphere->m_center = {0, 0, 0};
		sphere->m_material.m_color = {0, 1, 0};
		//objects
		scene.m_objects.push_back(plane);
		scene.m_objects.push_back(sphere);
		//scene
		scene.setup();
		scene.draw();
		scene.write_image("test.ppm", true);
	}
	catch(const std::exception& exception)
	{
		printf("%s\n", exception.what());
	}
	//return
	return EXIT_SUCCESS;
}