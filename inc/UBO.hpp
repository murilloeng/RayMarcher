#pragma once

//std
#include <cstdint>

//Ray Marcher
#include "RayMarcher/inc/Buffer.hpp"

class UBO : public Buffer
{
public:
	//constructor
	UBO(void);

	//destructor
	virtual ~UBO(void);

	//bind
	void bind_base(GLuint) const;
};