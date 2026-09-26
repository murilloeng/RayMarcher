//std
#include <cstdio>
#include <cstdlib>
#include <stdexcept>

//Ray Marcher
#include "RayMarcher/inc/Rasterizer/Color.hpp"
#include "RayMarcher/inc/Rasterizer/Scene.hpp"

namespace ray_marcher
{
	namespace rasterizer
	{
		//constructor
		Scene::Scene(void) : m_width{800}, m_height{800}, m_buffer{nullptr}
		{
			return;
		}
		
		//destructor
		Scene::~Scene(void)
		{
			delete[] m_buffer;
		}

		//draw
		void Scene::draw(void)
		{
			for(uint32_t i = 0; i < m_height; i++)
			{
				for(uint32_t j = 0; j < m_width; j++)
				{
					//data
					// const double u = 2 * double(j) / (m_width - 1) - 1;
					const double v = 1 - 2 * double(i) / (m_height - 1);
					uint8_t* buffer = m_buffer + 3 * m_width * i + 3 * j;
					//background
					Color((3 - v) / 4, (3 - v) / 4, 1).apply(buffer);
					
				}
			}
		}
		void Scene::setup(void)
		{
			delete[] m_buffer;
			m_buffer = new uint8_t[3 * m_width * m_height];
		}

		//write
		void Scene::write_image(const char* path, bool open) const
		{
			//data
			char command[256];
			FILE* file = fopen(path, "wb");
			//write
			fprintf(file, "P6 %d %d 255\n", m_width, m_height);
			fwrite(m_buffer, 1, 3 * m_width * m_height, file);
			//close
			fclose(file);
			//open
			if(open)
			{
				sprintf(command, "xdg-open %s&", path);
				if(system(command))
				{
					throw std::runtime_error("Unable to open file!");
				}
			}
		}
		void Scene::write_video(const char* path, bool open) const
		{
			return;
		}
	}
}