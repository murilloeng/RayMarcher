#pragma once

//std
#include <cstdint>

//OpenGL
#include <GL/gl.h>

class Buffer
{
public:
	//constructor
	Buffer(void);

	//destructor
	virtual ~Buffer(void);

	//data
	GLuint id(void) const;

	//GPU data
	void allocate(uint32_t);

	void retrieve(uint32_t, uint32_t, void*);

	void transfer(uint32_t, const void*);
	void transfer(uint32_t, uint32_t, const void*);

protected:
	//data
	GLuint m_id;
};