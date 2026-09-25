//std
#include <cstdlib>

//Ray Marcher
#include "RayMarcher/inc/Interface/Engine.hpp"

int main(void)
{
	//engine
	ray_marcher::interface::Engine().start();
	//return
	return EXIT_SUCCESS;
}