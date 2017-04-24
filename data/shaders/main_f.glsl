#version 330
#define PI 3.14159265359

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
uniform samplerCube irradiance_map;
uniform vec3 cam_pos;

uniform Light light;

in vec3 v_position;
in vec3 v_normal;
in vec2 v_texcoord;
in vec4 frag_pos;
in mat3 tbn_matrix;

uniform int use_textures;
uniform vec3 albedo_color;
uniform float roughness_factor;
uniform float metalic_factor;

float distri_ggx(vec3 N, vec3 H, float a)
{
    float a2 = a * a;
    float NdotH = pow(max(dot(N, H), 0.0), 2);
    return a2 / (pow(NdotH * (a2 - 1.0) + 1.0, 2) * PI);
}

float geom_schlick_ggx(float NdotV, float k)
{
    float nom   = NdotV;
    float denom = NdotV * (1.0 - k) + k;
    return nom / denom;
}

float geom_smith(vec3 N, vec3 V, vec3 L, float k)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx1 = geom_schlick_ggx(NdotV, k);
    float ggx2 = geom_schlick_ggx(NdotL, k);
    return ggx1 * ggx2;
}

vec3 fresnel_schlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}

void main(void)
{
	float roughness = pow(texture(roughness_texture, v_texcoord).r, 2.0);
	float metalic = texture(metalic_texture, v_texcoord).r;
	vec3 albedo = texture(albedo_texture, v_texcoord).rgb;

	if (use_textures == 0)
	{
		roughness = pow(roughness_factor, 2.0);
		metalic = metalic_factor;
		albedo = albedo_color;
	}

	vec3 normal = normalize(v_normal);
	vec3 view = normalize(cam_pos - frag_pos.xyz);
	vec3 light = normalize(vec3(1, 1, 1));


	vec3 F0 = mix(vec3(0.04), albedo, metalic);

	float dggx = distri_ggx(normal, normalize(view + light), roughness);
	float gs = geom_smith(normal, view, light, roughness + 0.1);
	vec3 fresnel = fresnel_schlick(dot(normalize(view + light), view), F0);

	vec3 nominator = dggx * gs * fresnel;
	float denominator = 4 * max(dot(normal, view), 0.0) * max(dot(normal, light), 0.0) + 0.001;
	vec3 brdf = nominator / denominator;

	vec3 kS = fresnel;
	vec3 kD = vec3(1.0) - kS;
	kD *= 1.0 - metalic;

	float NdotL = max(dot(normal, light), 0.0);

	vec3 irradiance = texture(irradiance_map, normal).rgb;
	vec3 ambient = irradiance * albedo;
	vec3 color = ambient + (kD * albedo / PI + brdf) * vec3(1, 1, 1) * NdotL;

	color = color / (color + vec3(1.0));
    color = pow(color, vec3(1.0/2.2));

	out_color = vec4(color, 1.0);
}
