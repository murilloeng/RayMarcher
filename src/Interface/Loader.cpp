//std
#include <stdexcept>

//OpenGL
#include <GL/glx.h>

//Ray Marcher
#include "RayMarcher/inc/Interface/API.hpp"
#include "RayMarcher/inc/Interface/Loader.hpp"

static void* load(const char* name)
{
	//load
	void* procedure = (void*) glXGetProcAddress((const GLubyte*) name);
	//check
	if(!procedure)
	{
		char msg[1024];
		sprintf(msg, "Error loading OpenGL function %s!", name);
		throw std::runtime_error(msg);
	}
	//return
	return procedure;
}

static void load_get(void)
{
	glGetBufferParameteriv = (PFNGLGETBUFFERPARAMETERIVPROC) load("glGetBufferParameteriv");
}
static void load_draw(void)
{
	glDrawArraysInstanced = (PFNGLDRAWARRAYSINSTANCEDPROC) load("glDrawArraysInstanced");
	glDrawElementsBaseVertex = (PFNGLDRAWELEMENTSBASEVERTEXPROC) load("glDrawElementsBaseVertex");
}
static void load_buffers(void)
{
	glIsBuffer = (PFNGLISBUFFERPROC) load("glIsBuffer");
	glBindBuffer = (PFNGLBINDBUFFERPROC) load("glBindBuffer");
	glCreateBuffers = (PFNGLCREATEBUFFERSPROC) load("glCreateBuffers");
	glDeleteBuffers = (PFNGLDELETEBUFFERSPROC) load("glDeleteBuffers");
	glBindBufferBase = (PFNGLBINDBUFFERBASEPROC) load("glBindBufferBase");
	glNamedBufferData = (PFNGLNAMEDBUFFERDATAPROC) load("glNamedBufferData");
	glNamedBufferSubData = (PFNGLNAMEDBUFFERSUBDATAPROC) load("glNamedBufferSubData");
	glGetNamedBufferSubData = (PFNGLGETNAMEDBUFFERSUBDATAPROC) load("glGetNamedBufferSubData");
}
static void load_shaders(void)
{
	glIsShader = (PFNGLISSHADERPROC) load("glIsShader");
	glGetShaderiv = (PFNGLGETSHADERIVPROC) load("glGetShaderiv");
	glCreateShader = (PFNGLCREATESHADERPROC) load("glCreateShader");
	glDeleteShader = (PFNGLDELETESHADERPROC) load("glDeleteShader");
	glShaderSource = (PFNGLSHADERSOURCEPROC) load("glShaderSource");
	glCompileShader = (PFNGLCOMPILESHADERPROC) load("glCompileShader");
	glMemoryBarrier = (PFNGLMEMORYBARRIERPROC) load("glMemoryBarrier");
	glDispatchCompute = (PFNGLDISPATCHCOMPUTEPROC) load("glDispatchCompute");
	glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC) load("glGetShaderInfoLog");
}
static void load_programs(void)
{
	glIsProgram = (PFNGLISPROGRAMPROC) load("glIsProgram");
	glUseProgram = (PFNGLUSEPROGRAMPROC) load("glUseProgram");
	glLinkProgram = (PFNGLLINKPROGRAMPROC) load("glLinkProgram");
	glAttachShader = (PFNGLATTACHSHADERPROC) load("glAttachShader");
	glGetProgramiv = (PFNGLGETPROGRAMIVPROC) load("glGetProgramiv");
	glCreateProgram = (PFNGLCREATEPROGRAMPROC) load("glCreateProgram");
	glDeleteProgram = (PFNGLDELETEPROGRAMPROC) load("glDeleteProgram");
	glValidateProgram = (PFNGLVALIDATEPROGRAMPROC) load("glValidateProgram");
	glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC) load("glGetProgramInfoLog");
	glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC) load("glGetUniformLocation");
}
static void load_textures(void)
{
	glCreateTextures = (PFNGLCREATETEXTURESPROC) load("glCreateTextures");
	glBindTextureUnit = (PFNGLBINDTEXTUREUNITPROC) load("glBindTextureUnit");
	glTextureStorage2D = (PFNGLTEXTURESTORAGE2DPROC) load("glTextureStorage2D");
	glTextureParameteri = (PFNGLTEXTUREPARAMETERIPROC) load("glTextureParameteri");
	glTextureSubImage2D = (PFNGLTEXTURESUBIMAGE2DPROC) load("glTextureSubImage2D");
	glGenerateTextureMipmap = (PFNGLGENERATETEXTUREMIPMAPPROC) load("glGenerateTextureMipmap");
}
static void load_vertex_arrays(void)
{
	glIsVertexArray = (PFNGLISVERTEXARRAYPROC) load("glIsVertexArray");
	glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC) load("glBindVertexArray");
	glCreateVertexArrays = (PFNGLCREATEVERTEXARRAYSPROC) load("glCreateVertexArrays");
	glEnableVertexArrayAttrib = (PFNGLENABLEVERTEXARRAYATTRIBPROC) load("glEnableVertexArrayAttrib");
	glVertexArrayVertexBuffer = (PFNGLVERTEXARRAYVERTEXBUFFERPROC) load("glVertexArrayVertexBuffer");
	glVertexArrayAttribFormat = (PFNGLVERTEXARRAYATTRIBFORMATPROC) load("glVertexArrayAttribFormat");
	glVertexArrayElementBuffer = (PFNGLVERTEXARRAYELEMENTBUFFERPROC) load("glVertexArrayElementBuffer");
	glVertexArrayAttribBinding = (PFNGLVERTEXARRAYATTRIBBINDINGPROC) load("glVertexArrayAttribBinding");
	glVertexArrayAttribIFormat = (PFNGLVERTEXARRAYATTRIBIFORMATPROC) load("glVertexArrayAttribIFormat");
	glVertexArrayAttribLFormat = (PFNGLVERTEXARRAYATTRIBLFORMATPROC) load("glVertexArrayAttribLFormat");
	glVertexArrayBindingDivisor = (PFNGLVERTEXARRAYBINDINGDIVISORPROC) load("glVertexArrayBindingDivisor");
}

namespace ray_marcher
{
	namespace interface
	{
		void load_functions(void)
		{
			load_get();
			load_draw();
			load_buffers();
			load_shaders();
			load_programs();
			load_textures();
			load_vertex_arrays();
		}
	}
}