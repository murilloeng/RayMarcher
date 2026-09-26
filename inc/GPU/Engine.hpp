#pragma once

//glfw
#include <GLFW/glfw3.h>

//Ray Marcher
#include "RayMarcher/inc/GPU/VAO.hpp"
#include "RayMarcher/inc/GPU/UBO.hpp"
#include "RayMarcher/inc/GPU/Data.hpp"
#include "RayMarcher/inc/GPU/Shader.hpp"

namespace ray_marcher
{
	namespace GPU
	{
		class Engine
		{
		public:
			//constructor
			Engine(void);
		
			//destructor
			~Engine(void);
		
			//start
			void start(void);
			virtual void update_scene(void);
		
			//setup
			void setup_glfw(void);
			void setup_scene(void);
			void setup_callbacks(void);
		
			//callbacks
			static void callback_size(GLFWwindow*, int32_t, int32_t);
			static void callback_key(GLFWwindow*, int32_t, int32_t, int32_t, int32_t);
		
			//data
			VAO* m_vao;
			UBO* m_ubo;
			Scene m_scene;
			Camera m_camera;
			Screen m_screen;
			Shader* m_shader;
			GLFWwindow* m_window;
			RayMarcher m_ray_marcher;
		};
	}
}