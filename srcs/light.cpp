#include "light.h"

Light::Light(vec3 dir, vec3 color, float intensity)
{
	m_direction = dir;
	m_color = color;
	m_intensity = intensity;
}

Light::~Light()
{}

void Light::bind(lz::Shader *shader)
{
	shader->setUniform("light.direction", m_direction.normalize());
	shader->setUniform("light.color", m_color);
	shader->setUniform("light.intensity", m_intensity);
}
