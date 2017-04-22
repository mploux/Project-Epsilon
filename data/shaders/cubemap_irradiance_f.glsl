#version 330
#define PI 3.14159265359

out vec4 out_color;

uniform samplerCube env_map;
uniform sampler2D env_tex;

in vec3 v_position;

void main(void)
{
	vec3 irradiance = vec3(0.0);

	vec3 normal = normalize(v_position);
	vec3 up = vec3(0.0, 1.0, 0.0);
	vec3 right = cross(up, normal);
	up = cross(normal, right);

	float sampleDelta = 1;

	float nrSamples = 0.0;
	for(float phi = 0.0; phi < 2.0 * PI; phi += sampleDelta)
	{
	    for(float theta = 0.0; theta < 0.5 * PI; theta += sampleDelta)
	    {
	        vec3 tangentSample = vec3(sin(theta) * cos(phi),  sin(theta) * sin(phi), sin(phi) * cos(theta));
	        vec3 sampleVec = tangentSample.x * right + tangentSample.y * up + tangentSample.z * normal;
	        irradiance += texture(env_map, sampleVec).rgb * cos(theta) * sin(theta);
	        nrSamples++;
	    }
	}
	irradiance = PI * irradiance * (1.0 / float(nrSamples));
	out_color = vec4(irradiance, 1.0);
}
