//std
#include <cstring>
#include <stdexcept>

//Ray Marcher
#include "RayMarcher/inc/API.hpp"
#include "RayMarcher/inc/Stage.hpp"
#include "RayMarcher/inc/Shader.hpp"

//constructors
Shader::Shader(const char* shader) : Shader({
	new Stage(GL_VERTEX_SHADER, std::string(shader) + ".vert"), 
	new Stage(GL_FRAGMENT_SHADER, std::string(shader) + ".frag")
})
{
	return;
}
Shader::Shader(std::vector<Stage*> stages)
{
	//create
	m_id = glCreateProgram();
	//check
	if(!glIsProgram(m_id))
	{
		throw std::runtime_error("Error creating shader program!");
	}
	//shaders
	for(Stage* stage : stages) glAttachShader(m_id, stage->m_id);
	//link
	GLint status;
	GLchar log[4096];
	glLinkProgram(m_id);
	glGetProgramiv(m_id, GL_LINK_STATUS, &status);
	if(status == 0)
	{
		glGetProgramInfoLog(m_id, sizeof(log), nullptr, log);
		throw std::runtime_error("Error linking shader program: " + std::string(log));
	}
	//validate
	glValidateProgram(m_id);
	glGetProgramiv(m_id, GL_VALIDATE_STATUS, &status);
	if(status == 0)
	{
		glGetProgramInfoLog(m_id, sizeof(log), nullptr, log);
		throw std::runtime_error("Error validating shader program: " + std::string(log));
	}
	//delete
	for(Stage* stage : stages) delete stage;
}

//destructor
Shader::~Shader(void)
{
	if(glIsProgram(m_id)) glDeleteProgram(m_id);
}

//data
GLuint Shader::id(void) const
{
	return m_id;
}

void Shader::add_path(std::string path)
{
	m_paths.push_back(path);
}
std::vector<std::string>& Shader::paths(void)
{
	return m_paths;
}

//bind
void Shader::bind(void) const
{
	glUseProgram(m_id);
}

//static members
std::vector<std::string> Shader::m_paths;