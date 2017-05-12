#include "mesh_renderer.h"

MeshRenderer::MeshRenderer(lz::Mesh *mesh, Material *mat)
{
	m_transform = new Transform();
	m_mesh = mesh;
	m_material = mat;
}

MeshRenderer::~MeshRenderer()
{
	delete m_transform;
}

void MeshRenderer::render(lz::Shader *shader)
{
	shader->setUniform("modelMatrix", m_transform->toMatrix());
	m_material->bind(shader);
	m_mesh->draw();
}
