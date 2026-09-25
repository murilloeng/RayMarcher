#pragma once

//std
#include <cstdint>

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
			uint32_t m_width;
			uint32_t m_height;
			uint8_t* m_buffer;
		};
	}
}