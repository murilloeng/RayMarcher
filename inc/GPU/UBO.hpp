#pragma once

//std
#include <cstdint>

//Ray Marcher
#include "RayMarcher/inc/GPU/Buffer.hpp"

namespace ray_marcher
{
	namespace GPU
	{
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
	}
}