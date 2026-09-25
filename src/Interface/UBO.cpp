//Ray Marcher
#include "RayMarcher/inc/Interface/API.hpp"
#include "RayMarcher/inc/Interface/UBO.hpp"

namespace ray_marcher
{
	namespace interface
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