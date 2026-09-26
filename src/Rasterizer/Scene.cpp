//std
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <stdexcept>

//Ray Marcher
#include "RayMarcher/inc/Rasterizer/Color.hpp"
#include "RayMarcher/inc/Rasterizer/Scene.hpp"
#include "RayMarcher/inc/Rasterizer/HitPoint.hpp"

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
			for(const Object* object : m_objects) delete object;
		}

		//draw
		void Scene::draw(void)
		{
			//data
			const Vec3 t2 = m_camera.m_up;
			const Vec3 t3 = (m_camera.m_position - m_camera.m_lookat).unit();
			const Vec3 t1 = t2.cross(t3);
			//draw
			for(uint32_t i = 0; i < m_height; i++)
			{
				for(uint32_t j = 0; j < m_width; j++)
				{
					//data
					HitPoint hit_point;
					Vec3 ray_position = m_camera.m_position;
					const double w = m_camera.m_focal_distance;
					const double u = 2 * double(j) / (m_width - 1) - 1;
					const double v = 1 - 2 * double(i) / (m_height - 1);
					uint8_t* buffer = m_buffer + 3 * m_width * i + 3 * j;
					const Vec3 ray_direction = (u * t1 + v * t2 - w * t3).unit();
					//background
					Color((3 - v) / 4, (3 - v) / 4, 1).apply(buffer);
					//mapping
					for(uint32_t k = 0; k < m_ray_marcher.m_iterations_max; k++)
					{
						double d = m_ray_marcher.m_distance_max;
						for(const Object* object : m_objects)
						{
							d = fmin(d, object->sdf(ray_position));
							if(d < m_ray_marcher.m_distance_min)
							{
								hit_point.m_status = true;
								hit_point.m_material = object->m_material;
								break;
							}
						}
						ray_position += d * ray_direction;
						if(hit_point.m_status || d > m_ray_marcher.m_distance_max) break;
					}
					if(hit_point.m_status) hit_point.m_material.m_color.apply(buffer);
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