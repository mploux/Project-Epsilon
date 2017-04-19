#version 330

layout (location = 0) in vec3 in_position;
layout (location = 1) in vec3 in_normal;
layout (location = 2) in vec2 in_texcoord;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

out vec3 v_position;
out vec3 v_normal;
out vec2 v_texcoord;
out vec4 frag_pos;

void main(void)
{
	v_position = in_position;
	v_normal = in_normal;
	v_texcoord = in_texcoord;
	frag_pos = viewMatrix * modelMatrix * vec4(in_position, 1.0);
	gl_Position = projectionMatrix * frag_pos;
}
