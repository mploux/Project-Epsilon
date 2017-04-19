#include "material.h"

Material::Material(const char *name)
{
	m_name = name;
	m_color = vec3(0, 0, 0);
	m_specularFactor = 0.0;
	m_specularPower = 0.0;
}

Material::~Material()
{}

void Material::addTexture(const char *name, Texture *texture)
{
	m_textures[name] = texture;
}

void Material::removeTexture(const char *name)
{
	(void) name;
}

void Material::bind(Shader *shader)
{
	int index = 0;
	for (const auto data : m_textures)
	{
		shader->setUniform(data.first, index);
		glActiveTexture(GL_TEXTURE0 + index);
		data.second->bind();
		index++;
	}
}
