#version 330
#define PI 3.14159265359

out vec4 out_color;

// uniform samplerCube env_map;
uniform sampler2D env_map;

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
	vec3 irradiance = vec3(0.0);
	vec3 normal = normalize(v_position);

	float samples = 10;
	for(float x = 0; x < samples; x++)
	{
		for(float y = 0; y < samples; y++)
		{
			for(float z = 0; z < samples; z++)
			{
				vec3 blur = normalize(vec3(
					((x / samples) * 2.0 - 1.0),
					((y / samples) * 2.0 - 1.0),
					((z / samples) * 2.0 - 1.0))
				);
				vec3 sampleVec = normalize(normal + blur);
				irradiance += texture(env_map, sphere_to_uv(normalize(sampleVec))).rgb;
			}
		}
	}
	out_color = vec4(irradiance / pow(samples, 3), 1.0);
}
