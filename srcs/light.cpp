#include "light.h"

Light::Light(vec3 pos, vec3 color, float intensity)
{
	m_position = pos;
	m_color = color;
	m_intensity = intensity;
}

Light::~Light()
{}

void Light::bind(lz::Shader *shader)
{
	shader->setUniform("light.position", m_position);
	shader->setUniform("light.color", m_color);
	shader->setUniform("light.intensity", m_intensity);
}
