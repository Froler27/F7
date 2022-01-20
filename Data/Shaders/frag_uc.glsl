#version 430

uniform vec4 color_u;

in vec4 color_v;
out vec4 color_f;

void main(void)
{
	color_f = color_u;
}