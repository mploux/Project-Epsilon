#version 330
#define PI 3.14159265359

out vec4 out_color;

struct Light
{
	vec3 direction;
	vec3 color;
	float intensity;
};

struct PBR_data
{
	float roughness;
	float metalic;
	vec3 albedo;
};

uniform sampler2D albedo_texture;
uniform sampler2D normal_texture;
uniform sampler2D roughness_texture;
uniform sampler2D metalic_texture;
uniform samplerCube env_map;
uniform samplerCube irradiance_map;
uniform sampler2D brdf_lut;
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

vec3 fresnel_schlick_roughness(float cosTheta, vec3 F0, float roughness)
{
    return F0 + (max(vec3(1.0 - roughness), F0) - F0) * pow(1.0 - cosTheta, 5.0);
}

vec3 PBR(PBR_data data, Light light, vec3 normal)
{
	vec3 view = normalize(cam_pos - frag_pos.xyz);
	vec3 reflected = reflect(-view, normal);

	vec3 F0 = mix(vec3(0.04), data.albedo, data.metalic);

	float dggx = distri_ggx(normal, normalize(view + light.direction), data.roughness);
	float gs = geom_smith(normal, view, light.direction, data.roughness + 0.1);
	vec3 fresnel = fresnel_schlick(dot(normalize(view + light.direction), view), F0);

	vec3 nominator = dggx * gs * fresnel;
	float denominator = 4 * max(dot(normal, view), 0.0) * max(dot(normal, light.direction), 0.0) + 0.001;
	vec3 brdf = nominator / denominator;

	vec3 kS = fresnel;
	vec3 kD = vec3(1.0) - kS;
	kD *= 1.0 - data.metalic;
	float NdotL = max(dot(normal, light.direction), 0.0);
	vec3 light_color = (kD * data.albedo / PI + brdf) * light.color * NdotL * light.intensity;
	//--

	vec3 fresnel_r = fresnel_schlick_roughness(max(dot(normal, view), 0.0), F0, data.roughness);

    vec3 kS_r = fresnel_r;
    vec3 kD_r = 1.0 - kS_r;
	kD_r *= 1.0 - data.metalic;

	vec3 irradiance = texture(irradiance_map, normal).rgb;
	vec3 diffuse = irradiance * data.albedo;

	vec3 specular_env = textureLod(env_map, reflected, data.roughness * 4).rgb;
	vec2 env_brdf  = texture(brdf_lut, vec2(max(dot(normal, view), 0.0), data.roughness)).rg;
	vec3 specular = specular_env * (fresnel_r * env_brdf.x + env_brdf.y);

	vec3 ambient = kD_r * diffuse + specular;
	return (ambient + light_color);
}

vec3 calc_normal_mapping(mat3 tbn_matrix, sampler2D normal_texture, vec2 texcoord)
{
	return (normalize(tbn_matrix * (2.0 * texture(normal_texture, texcoord).rgb - 1.0)));
}

void main(void)
{
	float roughness = texture(roughness_texture, v_texcoord).r;
	float metalic = texture(metalic_texture, v_texcoord).r;
	vec3 albedo = texture(albedo_texture, v_texcoord).rgb;

	if (use_textures == 0)
	{
		roughness = roughness_factor;
		metalic = metalic_factor;
		albedo = albedo_color;
	}

	vec3 normal = calc_normal_mapping(tbn_matrix, normal_texture, v_texcoord);

	PBR_data data;
	data.albedo = albedo;
	data.roughness = roughness;
	data.metalic = metalic;

	vec3 pbr_color = PBR(data, light, v_normal);

	out_color = vec4(pbr_color, 1.0);
}
