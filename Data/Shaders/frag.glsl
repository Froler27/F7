#version 430

in vec3 normal_v;
in vec4 color_v;
in vec2 texCoord_v;

out vec4 color_f;

uniform sampler2D texture0;

void main(void) 
{
	if (texCoord_v.x < 0.5) {
		color_f = texture(texture0, texCoord_v);
	} else { 
		color_f = color_v;
	}
}