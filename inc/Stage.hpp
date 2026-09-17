#pragma once

//std
#include <string>

//OpenGL
#include <GL/gl.h>

class Shader;

class Stage
{
public:
	//constructors
	Stage(GLenum, std::string);

	//constructors
	~Stage(void);

private:
	//read
	void read(std::string);
	void check(std::string&);

	//data
	GLuint m_id;
	char m_source[8192];

	//friends
	friend class Shader;
};