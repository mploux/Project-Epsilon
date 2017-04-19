#version 330

out vec4 out_color;

struct Light
{
	vec3 position;
	vec3 color;
	float intensity;
};

uniform sampler2D albedo_texture;
uniform sampler2D normal_texture;
uniform sampler2D roughness_texture;
uniform sampler2D metalic_texture;

uniform Light light;

in vec3 v_position;
in vec3 v_normal;
in vec2 v_texcoord;
in vec4 frag_pos;

void main(void)
{
	vec3 normal = v_normal;
	float light_dot = dot(normal, normalize(frag_pos.xyz - light.position));
	out_color = texture(albedo_texture, v_texcoord) * light_dot;
}
