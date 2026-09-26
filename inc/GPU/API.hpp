#pragma once

//OpenGL
#include <GL/gl.h>

//get
inline PFNGLGETBUFFERPARAMETERIVPROC glGetBufferParameteriv = nullptr;

//draw
inline PFNGLDRAWARRAYSINSTANCEDPROC glDrawArraysInstanced = nullptr;
inline PFNGLDRAWELEMENTSBASEVERTEXPROC glDrawElementsBaseVertex = nullptr;

//buffers
inline PFNGLISBUFFERPROC glIsBuffer = nullptr;
inline PFNGLBINDBUFFERPROC glBindBuffer = nullptr;
inline PFNGLCREATEBUFFERSPROC glCreateBuffers = nullptr;
inline PFNGLDELETEBUFFERSPROC glDeleteBuffers = nullptr;
inline PFNGLBINDBUFFERBASEPROC glBindBufferBase = nullptr;
inline PFNGLNAMEDBUFFERDATAPROC glNamedBufferData = nullptr;
inline PFNGLNAMEDBUFFERSUBDATAPROC glNamedBufferSubData = nullptr;
inline PFNGLGETNAMEDBUFFERSUBDATAPROC glGetNamedBufferSubData = nullptr;

//vertex arrays
inline PFNGLISVERTEXARRAYPROC glIsVertexArray = nullptr;
inline PFNGLBINDVERTEXARRAYPROC glBindVertexArray = nullptr;
inline PFNGLCREATEVERTEXARRAYSPROC glCreateVertexArrays = nullptr;
inline PFNGLENABLEVERTEXARRAYATTRIBPROC glEnableVertexArrayAttrib = nullptr;
inline PFNGLVERTEXARRAYVERTEXBUFFERPROC glVertexArrayVertexBuffer = nullptr;
inline PFNGLVERTEXARRAYATTRIBFORMATPROC glVertexArrayAttribFormat = nullptr;
inline PFNGLVERTEXARRAYATTRIBIFORMATPROC glVertexArrayAttribIFormat = nullptr;
inline PFNGLVERTEXARRAYATTRIBLFORMATPROC glVertexArrayAttribLFormat = nullptr;
inline PFNGLVERTEXARRAYELEMENTBUFFERPROC glVertexArrayElementBuffer = nullptr;
inline PFNGLVERTEXARRAYATTRIBBINDINGPROC glVertexArrayAttribBinding = nullptr;
inline PFNGLVERTEXARRAYBINDINGDIVISORPROC glVertexArrayBindingDivisor = nullptr;

//textures
inline PFNGLCREATETEXTURESPROC glCreateTextures = nullptr;
inline PFNGLBINDTEXTUREUNITPROC glBindTextureUnit = nullptr;
inline PFNGLTEXTURESTORAGE2DPROC glTextureStorage2D = nullptr;
inline PFNGLTEXTUREPARAMETERIPROC glTextureParameteri = nullptr;
inline PFNGLTEXTURESUBIMAGE2DPROC glTextureSubImage2D = nullptr;
inline PFNGLGENERATETEXTUREMIPMAPPROC glGenerateTextureMipmap = nullptr;

//shaders
inline PFNGLISSHADERPROC glIsShader = nullptr;
inline PFNGLGETSHADERIVPROC glGetShaderiv = nullptr;
inline PFNGLCREATESHADERPROC glCreateShader = nullptr;
inline PFNGLDELETESHADERPROC glDeleteShader = nullptr;
inline PFNGLSHADERSOURCEPROC glShaderSource = nullptr;
inline PFNGLCOMPILESHADERPROC glCompileShader = nullptr;
inline PFNGLMEMORYBARRIERPROC glMemoryBarrier = nullptr;
inline PFNGLDISPATCHCOMPUTEPROC glDispatchCompute = nullptr;
inline PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog = nullptr;

//programs
inline PFNGLISPROGRAMPROC glIsProgram = nullptr;
inline PFNGLUSEPROGRAMPROC glUseProgram = nullptr;
inline PFNGLLINKPROGRAMPROC glLinkProgram = nullptr;
inline PFNGLATTACHSHADERPROC glAttachShader = nullptr;
inline PFNGLGETPROGRAMIVPROC glGetProgramiv = nullptr;
inline PFNGLCREATEPROGRAMPROC glCreateProgram = nullptr;
inline PFNGLDELETEPROGRAMPROC glDeleteProgram = nullptr;
inline PFNGLVALIDATEPROGRAMPROC glValidateProgram = nullptr;
inline PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog = nullptr;
inline PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation = nullptr;