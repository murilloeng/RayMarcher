#pragma once

//std
#include <vector>
#include <cstdint>

//Ray Marcher
#include "RayMarcher/inc/Rasterizer/Camera.hpp"
#include "RayMarcher/inc/Rasterizer/Object.hpp"
#include "RayMarcher/inc/Rasterizer/RayMarcher.hpp"

namespace ray_marcher
{
	namespace rasterizer
	{
		class Scene
		{
		public:
			//constructor
			Scene(void);

			//destructor
			~Scene(void);

			//draw
			void draw(void);
			void setup(void);

			//write
			void write_image(const char*, bool = false) const;
			void write_video(const char*, bool = false) const;

			//data
			Camera m_camera;
			uint32_t m_width;
			uint32_t m_height;
			uint8_t* m_buffer;
			RayMarcher m_ray_marcher;
			std::vector<Object*> m_objects;
		};
	}
}