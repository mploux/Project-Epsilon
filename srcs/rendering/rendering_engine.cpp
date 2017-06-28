#include "rendering/rendering_engine.h"

RenderingEngine::RenderingEngine():
	m_brdf_lut { lz::Resources::loadTexture("data/environments/BRDF_LUT.dds") }
{
}

RenderingEngine::~RenderingEngine()
{
	m_meshes.clear();
}

void RenderingEngine::bindShader()
{
	m_shader->bind();
	m_shader->setUniform("use_textures", 1);
	m_light->bind(m_shader);
	m_shader->setUniform("cam_pos", m_camera->getTransform().getPosition());
	m_shader->setUniform("projectionMatrix", m_camera->getProjectionMatrix());
	m_shader->setUniform("viewMatrix", m_camera->getViewMatrix());

	glActiveTexture(GL_TEXTURE5);
	m_shader->setUniform("env_map", 5);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_envMap->getID());

	glActiveTexture(GL_TEXTURE6);
	m_shader->setUniform("irradiance_map", 6);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_envMap->getIrradianceID());

	glActiveTexture(GL_TEXTURE7);
	m_shader->setUniform("brdf_lut", 7);
	m_brdf_lut->bind();
}

void RenderingEngine::render()
{
	bindShader();
	for (uint32_t i = 0; i < m_meshes.size(); i++)
		m_meshes[i]->render(m_shader);
}
