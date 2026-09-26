//std
#include <cmath>
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
			#pragma omp parallel for schedule(dynamic, 4)
			for(uint32_t i = 0; i < m_height; i++)
			{
				for(uint32_t j = 0; j < m_width; j++)
				{
					//data
					HitData hit_point;
					const double w = m_camera.m_focal_distance;
					const double u = 2 * double(j) / (m_width - 1) - 1;
					const double v = 1 - 2 * double(i) / (m_height - 1);
					uint8_t* buffer = m_buffer + 3 * m_width * i + 3 * j;
					const Vec3 ray_direction = (u * t1 + v * t2 - w * t3).unit();
					//background
					Color((3 - v) / 4, (3 - v) / 4, 1).apply(buffer);
					//ray marching
					if(ray_march(m_camera.m_position, ray_direction, hit_point))
					{
						//shadow
						double ds = fmax(0, -m_light.m_direction.inner(hit_point.m_normal));
						if(ds > 0)
						{
							const Vec3 normal = hit_point.m_normal;
							const Vec3 position = hit_point.m_position;
							const double distance = m_ray_marcher.m_distance_min;
							ds *= !occlusion(position + 1.1 * distance* normal, -m_light.m_direction);
						}
						//color
						const Color color_ambient = m_light.m_ambient * hit_point.m_material.m_color;
						const Color color_diffuse = m_light.m_diffuse * hit_point.m_material.m_color;
						(color_ambient + ds * color_diffuse).apply(buffer);
					}
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

		//ray marching
		bool Scene::occlusion(const Vec3& ray_origin, const Vec3& ray_direction) const
		{
			//data
			double ray_length = 0;
			Vec3 ray_position = ray_origin;
			//march
			for(uint32_t iteration = 0; iteration < m_ray_marcher.m_iterations_max; iteration++)
			{
				double d = m_ray_marcher.m_distance_max;
				for(const Object* object : m_objects)
				{
					d = fmin(d, object->sdf(ray_position));
					if(d < m_ray_marcher.m_distance_min) return true;
				}
				ray_length += d;
				ray_position += d * ray_direction;
				if(ray_length > m_ray_marcher.m_distance_max) return false;
			}
			//return
			return false;
		}
		bool Scene::ray_march(const Vec3& ray_origin, const Vec3& ray_direction, HitData& hit_point) const
		{
			//data
			double ray_length = 0;
			Vec3 ray_position = ray_origin;
			//march
			for(uint32_t iteration = 0; iteration < m_ray_marcher.m_iterations_max; iteration++)
			{
				double d = m_ray_marcher.m_distance_max;
				for(const Object* object : m_objects)
				{
					d = fmin(d, object->sdf(ray_position));
					if(d < m_ray_marcher.m_distance_min)
					{
						hit_point.m_position = ray_position;
						hit_point.m_material = object->m_material;
						hit_point.m_normal = object->normal(ray_position);
						return true;
					}
				}
				ray_length += d;
				ray_position += d * ray_direction;
				if(ray_length > m_ray_marcher.m_distance_max) return false;
			}
			//return
			return false;
		}
	}
}