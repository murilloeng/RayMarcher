//std
#include <cstdlib>
#include <stdexcept>

//glfw
#include <GL/glx.h>
#include <GLFW/glfw3.h>

//Ray Marcher
#include "RayMarcher/inc/API.hpp"
#include "RayMarcher/inc/VAO.hpp"
#include "RayMarcher/inc/UBO.hpp"
#include "RayMarcher/inc/Loader.hpp"
#include "RayMarcher/inc/Shader.hpp"

//static
static VAO* vao;
static UBO* ubo;
static Shader* shader;
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

//setup
static void setup_glfw(void)
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
	//OpenGL API
	load_functions();
	Shader::add_path("shd/");
}
static void setup_scene(void)
{
	//data
	vao = new VAO;
	ubo = new UBO;
	shader = new Shader("base");
	const float ubo_data[] = {0, 0, 0};
	//ubo
	ubo->bind_base(0);
	ubo->transfer(3 * sizeof(float), ubo_data);
}

//cleanup
static void cleanup(void)
{
	delete vao;
	delete ubo;
	delete shader;
	glfwDestroyWindow(window);
	glfwTerminate();
}

int main(void)
{
	setup_glfw();
	setup_scene();
	//callbacks
	glfwSetKeyCallback(window, callback_key);
	//draw loop
	while(!glfwWindowShouldClose(window))
	{
		vao->bind();
		shader->bind();
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glfwSwapBuffers(window);
	}
	//return
	cleanup();
	return EXIT_SUCCESS;
}