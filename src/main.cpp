//std
#include <cstdlib>

//Ray Marcher
#include "RayMarcher/inc/Interface/Engine.hpp"
#include "RayMarcher/inc/Rasterizer/Scene.hpp"

int main(void)
{
	try
	{
		//data
		ray_marcher::rasterizer::Scene scene;
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