#pragma once

//std
#include <cstdint>

class Scenne
{
public:
	//constructor
	Scenne(void);

	//destructor
	~Scenne(void);

	//draw
	void draw(void);
	void setup(void);

	//write
	void write_image(const char*) const;
	void write_video(const char*) const;

	//data
	uint32_t m_width;
	uint32_t m_height;
	uint8_t* m_buffer;
};