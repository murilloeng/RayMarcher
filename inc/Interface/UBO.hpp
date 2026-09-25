#pragma once

//std
#include <cstdint>

//Ray Marcher
#include "RayMarcher/inc/Interface/Buffer.hpp"

namespace ray_marcher
{
	namespace interface
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