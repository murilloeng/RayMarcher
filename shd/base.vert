#version 460 core

vec2 positions[4] = vec2[4](
	vec2(-1, -1),
	vec2(+1, -1),
	vec2(-1, +1),
	vec2(+1, +1)
);

void main(void)
{
	gl_Position = vec4(positions[gl_VertexID], 0, 1);
}
