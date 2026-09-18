//Ray Marcher
#include "RayMarcher/inc/API.hpp"
#include "RayMarcher/inc/UBO.hpp"

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