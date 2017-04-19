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
uniform samplerCube env_map;
uniform vec3 cam_pos;

uniform Light light;

in vec3 v_position;
in vec3 v_normal;
in vec2 v_texcoord;
in vec4 frag_pos;

void main(void)
{
	vec3 normal = v_normal;
	float light_dot = dot(normal, -normalize(frag_pos.xyz - light.position)) * 0.5 + 0.5;
	vec4 color = texture(albedo_texture, v_texcoord);
	vec4 metal_color = texture(env_map, reflect(normalize(frag_pos.xyz - cam_pos), v_normal));
	out_color = mix(color, metal_color, texture(metalic_texture, v_texcoord).r) * light_dot;
}
