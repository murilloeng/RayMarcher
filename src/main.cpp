//std
#include <cstdlib>

//Ray Marcher
#include "RayMarcher/inc/Interface/Engine.hpp"
#include "RayMarcher/inc/Rasterizer/Scene.hpp"

int main(void)
{
	//data
	ray_marcher::rasterizer::Scene scene;
	//scene
	scene.setup();
	scene.draw();
	scene.write_image("test.ppm");
	//engine
	// ray_marcher::interface::Engine().start();
	//return
	return EXIT_SUCCESS;
}