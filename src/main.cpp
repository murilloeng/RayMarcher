//std
#include <cstdlib>
#include <stdexcept>

//glfw
#include <GL/glx.h>
#include <GLFW/glfw3.h>

//Ray Marcher
#include "RayMarcher/inc/API.hpp"
#include "RayMarcher/inc/Loader.hpp"

//static
static GLFWwindow* window;

//callbacks
static void callback_key(GLFWwindow* window, int32_t key, int32_t scancode, int32_t action, int32_t mods)
{
	//data
	double x1, x2;
	glfwGetCursorPos(window, &x1, &x2);
	//check
	if(action == GLFW_RELEASE) return;
	//close
	if(key == GLFW_KEY_ESCAPE)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

int main(void)
{
	//library
	if(glfwInit() != GLFW_TRUE)
	{
		throw std::runtime_error("GLFW initialization failed!");
	}
	//window
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = glfwCreateWindow(900, 900, "Ray Marcher", nullptr, nullptr);
	if(!window)
	{
		glfwTerminate();
		throw std::runtime_error("GLFW window initialization failed!");
	}
	//context
	glfwMakeContextCurrent(window);
	//v-sync
	glfwSwapInterval(0);
	//functions
	load_functions();

	//callbacks
	glfwSetKeyCallback(window, callback_key);
	//draw loop
	while(!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT);
		
		glfwSwapBuffers(window);
	}
	//return
	return EXIT_SUCCESS;
}