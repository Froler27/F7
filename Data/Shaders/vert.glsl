#version 430

layout (location = 0) in vec3 position;

out vec4 color_v;

uniform mat4 world_mat_u;
uniform mat4 view_mat_u;
uniform mat4 proj_mat_u;
//uniform vec4 color_u;

void main(void)
{
	gl_Position = proj_mat_u * view_mat_u * world_mat_u * vec4(position, 1.0);
	color_v = vec4(1,0,0,1);
}
