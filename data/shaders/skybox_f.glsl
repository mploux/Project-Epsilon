#version 330

out vec4 out_color;

uniform samplerCube env_map;

in vec3 v_position;

void main(void)
{
	out_color = texture(env_map, -normalize(v_position));
}
