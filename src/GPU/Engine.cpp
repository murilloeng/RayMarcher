//std
#include <stdexcept>

//Ray Marcher
#include "RayMarcher/inc/GPU/Engine.hpp"
#include "RayMarcher/inc/GPU/Loader.hpp"
#include "RayMarcher/inc/GPU/Shader.hpp"

namespace ray_marcher
{
	namespace GPU
	{
		//constructor
		Engine::Engine(void) : m_vao{nullptr}, m_ubo{nullptr}, m_shader{nullptr}, m_window{nullptr}
		{
			setup_glfw();
			setup_scene();
			setup_callbacks();
		}
		
		//destructor
		Engine::~Engine(void)
		{
			delete m_vao;
			delete m_ubo;
			delete m_shader;
			glfwDestroyWindow(m_window);
			glfwTerminate();
		}
		
		//start
		void Engine::start(void)
		{
			glfwSetTime(0);
			while(!glfwWindowShouldClose(m_window))
			{
				m_vao->bind();
				m_shader->bind();
				glfwPollEvents();
				m_camera.m_time = (float) glfwGetTime();
				update_scene();
				m_ubo->transfer(0, sizeof(Scene), &m_scene);
				m_ubo->transfer(sizeof(Scene) + sizeof(Screen), sizeof(Camera), &m_camera);
				glClear(GL_COLOR_BUFFER_BIT);
				glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
				glfwSwapBuffers(m_window);
			}
		}
		void Engine::update_scene(void)
		{
			return;
		}
		
		//setup
		void Engine::setup_glfw(void)
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
			m_window = glfwCreateWindow(900, 900, "Ray Marcher", nullptr, nullptr);
			if(!m_window)
			{
				glfwTerminate();
				throw std::runtime_error("GLFW window initialization failed!");
			}
			//context
			glfwMakeContextCurrent(m_window);
			glfwSetWindowUserPointer(m_window, this);
			//v-sync
			glfwSwapInterval(0);
			//OpenGL API
			load_functions();
			Shader::add_path("shd/");
		}
		void Engine::setup_scene(void)
		{
			//data
			m_vao = new VAO;
			m_ubo = new UBO;
			m_shader = new Shader("base");
			//ubo setup
			m_ubo->bind_base(0);
			glfwGetWindowSize(m_window, &m_screen.m_width, &m_screen.m_height);
			m_ubo->allocate(sizeof(Scene) + sizeof(Screen) + sizeof(Camera) + sizeof(RayMarcher));
			//ubo transfer
			m_ubo->transfer(0, sizeof(Scene), &m_scene);
			m_ubo->transfer(sizeof(Scene), sizeof(Screen), &m_screen);
			m_ubo->transfer(sizeof(Scene) + sizeof(Screen), sizeof(Camera), &m_camera);
			m_ubo->transfer(sizeof(Scene) + sizeof(Screen) + sizeof(Camera), sizeof(RayMarcher), &m_ray_marcher);
		}
		void Engine::setup_callbacks(void)
		{
			glfwSetKeyCallback(m_window, Engine::callback_key);
			glfwSetWindowSizeCallback(m_window, Engine::callback_size);
		}
		
		//callbacks
		void Engine::callback_size(GLFWwindow* window, int32_t width, int32_t height)
		{
			//data
			UBO* ubo = ((Engine*) glfwGetWindowUserPointer(window))->m_ubo;
			Screen& screen = ((Engine*) glfwGetWindowUserPointer(window))->m_screen;
			//update
			screen.m_width = width;
			screen.m_height = height;
			glViewport(0, 0, width, height);
			ubo->transfer(sizeof(Scene), sizeof(Screen), &screen);
		}
		void Engine::callback_key(GLFWwindow* window, int32_t key, int32_t scancode, int32_t action, int32_t mods)
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
	}
}