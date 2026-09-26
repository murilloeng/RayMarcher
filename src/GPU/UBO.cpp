//Ray Marcher
#include "RayMarcher/inc/GPU/API.hpp"
#include "RayMarcher/inc/GPU/UBO.hpp"

namespace ray_marcher
{
	namespace GPU
	{
		//constructor
		UBO::UBO(void)
		{
			return;
		}
		
		//destructor
		UBO::~UBO(void)
		{
			return;
		}
		
		//bind
		void UBO::bind_base(GLuint index) const
		{
			glBindBufferBase(GL_UNIFORM_BUFFER, index, m_id);
		}
	}
}