#include "material.h"

Material::Material(char *name, Shader *shader)
{
	m_name = name;
	m_shader = shader;
}

Material::~Material()
{

}

void Material::addTexture(char *name, Texture *texture)
{
	m_textures->insert()
}

void Material::removeTexture(char *name)
{
}

void Material::bind()
{
	int index = 0;
	for (const auto data : m_textures)
	{
		std::cout << data->first << " : " << std::endl;
		m_shader.setUniform(data->first, index);
		glActiveTexture(GL_TEXTURE0 + index);
		data->second->bind();
		index++;
	}
	// m_shader.setUniform((char*)"normal_texture", 1);
	// m_shader.setUniform((char*)"roughness_texture", 2);
	// m_shader.setUniform((char*)"metalic_texture", 3);
}
