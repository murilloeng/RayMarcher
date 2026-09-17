#pragma once

//std
#include <string>
#include <vector>
#include <cstdint>

//OpenGL
#include <GL/gl.h>

class Stage;

class Shader
{
public:
	//constructors
	Shader(const char*);
	Shader(std::vector<Stage*>);

	//destructor
	~Shader(void);

	//bind
	void bind(void) const;

	//data
	GLuint id(void) const;

	static void add_path(std::string);
	static std::vector<std::string>& paths(void);

private:
	//data
	GLuint m_id;
	static std::vector<std::string> m_paths;
};