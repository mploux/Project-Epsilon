#version 330

layout (location = 0) in vec3 in_position;
layout (location = 1) in vec3 in_normal;
layout (location = 3) in vec3 in_tangent;

out VS_OUT {
    vec3 normal;
    vec3 tangent;
    vec3 bitangent;
} vs_out;

void main(void)
{
	vs_out.normal = in_normal;
	vs_out.tangent = in_tangent;
	vs_out.bitangent = cross(vs_out.tangent, vs_out.normal);
	gl_Position = vec4(in_position, 1.0);
}
