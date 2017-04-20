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
in mat3 tbn_matrix;

void main(void)
{
	float roughness = texture(roughness_texture, v_texcoord).r;
	float metalic = texture(metalic_texture, v_texcoord).r;
	vec4 albedo = texture(albedo_texture, v_texcoord);

	vec3 normal = normalize(tbn_matrix * (texture(normal_texture, v_texcoord).rgb * 2.0 - 1.0));
	float light_dot = dot(normal, -normalize(frag_pos.xyz - light.position));

	float fresnel = 1.0 - clamp(dot(normal, -normalize(frag_pos.xyz - cam_pos)) * 1.2, 0, 1);
	vec4 metal_color = texture(env_map, reflect(-normalize(frag_pos.xyz - cam_pos), normal));


	// color = vec4(1, 1, 1, 1);
	float factor = (albedo.x + albedo.y + albedo.z) / 3.0;
	out_color = mix(albedo * light_dot, metal_color, fresnel * metalic) * roughness;
}
