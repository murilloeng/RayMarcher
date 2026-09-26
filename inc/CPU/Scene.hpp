#pragma once

//std
#include <vector>
#include <cstdint>

//Ray Marcher
#include "RayMarcher/inc/CPU/Light.hpp"
#include "RayMarcher/inc/CPU/Camera.hpp"
#include "RayMarcher/inc/CPU/Object.hpp"
#include "RayMarcher/inc/CPU/HitData.hpp"
#include "RayMarcher/inc/CPU/RayMarcher.hpp"

namespace ray_marcher
{
	namespace CPU
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

			//ray marching
			bool occlusion(const Vec3&, const Vec3&) const;
			bool ray_march(const Vec3&, const Vec3&, HitData&) const;

			//data
			Light m_light;
			Camera m_camera;
			uint32_t m_width;
			uint32_t m_height;
			uint8_t* m_buffer;
			RayMarcher m_ray_marcher;
			std::vector<Object*> m_objects;
		};
	}
}