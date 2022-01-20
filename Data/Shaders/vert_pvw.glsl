#version 430

uniform mat4 world_matrix;
uniform mat4 view_matrix;
uniform mat4 proj_matrix;

layout (location = 0) in vec3 position;

out vec4 color_v;

void main(void)
{
	gl_Position = proj_matrix * view_matrix * world_matrix * vec4(position,1);
	color_v = vec4(0,0,0,1);
}
