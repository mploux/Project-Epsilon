#version 330
#define PI 3.14159265359

out vec4 out_color;

uniform samplerCube env_map;
uniform sampler2D env_tex;

in vec3 v_position;

void main(void)
{
	vec3 color = textureLod(env_map, normalize(v_position), 0).rgb;
	out_color = vec4(color, 1.0);
}
