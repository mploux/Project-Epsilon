#ifndef MESHRENDERER_H
# define MESHRENDERER_H

# include <LZ/transform.h>
# include <LZ/mesh.h>
# include <LZ/maths.h>
# include <LZ/maths.h>
# include "material.h"

using namespace lz::maths;

class MeshRenderer
{
private:
	lz::Transform *m_transform;
	lz::Mesh *m_mesh;
	Material *m_material;

public:
	MeshRenderer(lz::Mesh *mesh, Material *mat);
	~MeshRenderer();

	void render(lz::Shader *shader);

	inline void setPosition(vec3 pos) { m_transform->setPosition(pos); }
	inline void setRotation(quat rot) { m_transform->setRotation(rot); }
	inline void setScale(vec3 scale) { m_transform->setScale(scale); }
	inline void setTransform(lz::Transform *trs) { m_transform = trs; }

	inline lz::Transform *getTransform() { return m_transform; }
	inline lz::Mesh *getMesh() { return m_mesh; }
	inline Material *getMaterial() { return m_material; }
};

#endif
