#version 330
#define PI 3.14159265359

out vec4 out_color;

uniform samplerCube env_map;
uniform sampler2D env_tex;

in vec3 v_position;

vec2 sphere_to_uv(vec3 v)
{
    vec2 uv = vec2(atan(v.z, v.x), asin(v.y));
    uv *= vec2(0.1591, 0.3183);
    uv += 0.5;
    return uv;
}

void main(void)
{
	vec3 color = texture(env_map, normalize(v_position)).rgb;
	out_color = vec4(color, 1.0);
}
