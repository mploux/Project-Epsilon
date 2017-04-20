#version 330

layout (location = 0) in vec3 in_position;
layout (location = 1) in vec3 in_normal;
layout (location = 2) in vec2 in_texcoord;
layout (location = 3) in vec3 in_tangent;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

out vec3 v_position;
out vec3 v_normal;
out vec3 v_tangent;
out vec2 v_texcoord;
out vec4 frag_pos;
out mat3 tbn_matrix;

void main(void)
{
	v_position = in_position;
	v_normal = (modelMatrix * vec4(in_normal, 0.0)).xyz;
	v_tangent = (modelMatrix * vec4(in_tangent, 0.0)).xyz;
	v_tangent = normalize(v_tangent - dot(v_tangent, v_normal) * v_normal);
	vec3 biTangent = cross(v_tangent, v_normal);
	tbn_matrix = mat3(v_tangent, biTangent, v_normal);
	v_texcoord = in_texcoord;
	frag_pos = modelMatrix * vec4(in_position, 1.0);
	gl_Position = projectionMatrix * viewMatrix * frag_pos;
}
