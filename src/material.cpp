#include "material.hpp"

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
	m_texture = texture;
}
void Material::removeTexture(char *name)
{
	m_texture = texture;
}

void Material::bind()
{

}
