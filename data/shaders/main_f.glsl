#version 330

out vec4 out_color;

uniform sampler2D albedo_texture;
uniform sampler2D normal_texture;
uniform sampler2D roughness_texture;
uniform sampler2D metalic_texture;

in vec3 v_position;
in vec2 v_texcoord;
in vec3 frag_pos;

void main(void)
{
	if (frag_pos.x > 0.2)
		out_color = texture(albedo_texture, v_texcoord);
	else if (frag_pos.x > 0)
		out_color = texture(normal_texture, v_texcoord);
	else if (frag_pos.x > -0.2)
		out_color = texture(roughness_texture, v_texcoord);
	else
		out_color = texture(metalic_texture, v_texcoord);
}
