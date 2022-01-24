#version 430

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec4 color;
layout (location = 3) in vec2 texCoord;

out vec3 normal_v;
out vec4 color_v;
out vec2 texCoord_v;

uniform mat4 world_mat_u;
uniform mat4 view_mat_u;
uniform mat4 proj_mat_u;
//uniform vec4 color_u;


void main(void)
{
	gl_Position = proj_mat_u * view_mat_u * world_mat_u * vec4(position, 1.0);
	normal_v = normal;
	color_v = color;
	texCoord_v = texCoord;
}
