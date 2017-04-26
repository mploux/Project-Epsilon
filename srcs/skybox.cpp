#include "skybox.h"

Skybox::Skybox(lz::Cubemap *cubemap)
{
	m_cubemap = cubemap;
	m_shader = new lz::Shader("data/shaders/skybox_v.glsl", "data/shaders/skybox_f.glsl");
	Skybox::generateCubeMesh();
}

Skybox::~Skybox()
{}

void Skybox::generateCubeMesh()
{
	// TODO: Generate the mesh
	m_cube = lz::Resources::loadObj("data/models/Cube.obj")->getMesh();
}

void Skybox::render(lz::Camera *camera)
{
	m_shader->bind();
	glActiveTexture(GL_TEXTURE0);
	m_shader->setUniform("env_map", 0);
	m_cubemap->bind();
	m_shader->setUniform("projectionMatrix", camera->getProjectionMatrix());
	m_shader->setUniform("viewMatrix", mat4::cameraView(camera->getTransform().getForward(), camera->getTransform().getUp()));
	m_shader->setUniform("modelMatrix", mat4::identity());
	glDepthMask(GL_FALSE);
	glCullFace(GL_BACK);
	m_cube->draw();
	glCullFace(GL_FRONT);
	glDepthMask(GL_TRUE);
	m_shader->unbind();
}
