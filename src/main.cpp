//std
#include <cstdlib>
#include <stdexcept>

//glfw
#include <GLFW/glfw3.h>

//Ray Marcher
#include "RayMarcher/inc/API.hpp"
#include "RayMarcher/inc/VAO.hpp"
#include "RayMarcher/inc/UBO.hpp"
#include "RayMarcher/inc/Loader.hpp"
#include "RayMarcher/inc/Shader.hpp"

//defines
#define MAX_PLANES 100
#define MAX_SPHERES 100

//structures
struct alignas(16) Screen
{
	int32_t m_width;
	int32_t m_height;
};
struct alignas(16) Camera
{
	float m_up[4];
	float m_look_at[4];
	float m_position[3];
	float m_time, m_focal_distance;
};
struct alignas(16) RayMarcher
{
	uint32_t m_iteration_max = 100;
	float m_distance_min = 1.00e-05f;
	float m_distance_max = 1.00e+05f;
};
struct Plane
{
	float point[4];
	float normal[4];
};
struct Sphere
{
	float center[4];
	float radius;
};
struct Scene
{
	uint32_t m_counter_planes;
	uint32_t m_counter_spheres;
	Plane m_planes[MAX_PLANES];
	Sphere m_spheres[MAX_SPHERES];
};

//data
static VAO* vao;
static UBO* ubo;
static Screen screen;
static Camera camera;
static Shader* shader;
static GLFWwindow* window;
static RayMarcher ray_marcher;

//callbacks
static void callback_size(GLFWwindow* window, int32_t width, int32_t height)
{
	screen.m_width = width;
	screen.m_height = height;
	glViewport(0, 0, width, height);
	ubo->transfer(0, sizeof(screen), &screen);
}
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
	const uint32_t screen_size = sizeof(Screen);
	const uint32_t camera_size = sizeof(Camera);
	const uint32_t ray_marcher_size = sizeof(RayMarcher);
	//ubo setup
	ubo->bind_base(0);
	ubo->allocate(screen_size + camera_size + ray_marcher_size);
	glfwGetWindowSize(window, &screen.m_width, &screen.m_height);
	//ubo transfer
	ubo->transfer(0, screen_size, &screen);
	ubo->transfer(screen_size, camera_size, &camera);
	ubo->transfer(screen_size + camera_size, ray_marcher_size, &ray_marcher);
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
	glfwSetWindowSizeCallback(window, callback_size);
	//draw loop
	glfwSetTime(0);
	while(!glfwWindowShouldClose(window))
	{
		vao->bind();
		shader->bind();
		glfwPollEvents();
		camera.m_time = (float) glfwGetTime();
		ubo->transfer(sizeof(Screen), sizeof(Camera), &camera);
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glfwSwapBuffers(window);
	}
	//return
	cleanup();
	return EXIT_SUCCESS;
}