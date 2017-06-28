#ifndef RENDERING_ENGINE_H
# define RENDERING_ENGINE_H

# include <LZ/lz.h>
# include <iostream>

# include "rendering/mesh_renderer.h"
# include "light.h"

using namespace lz;

class RenderingEngine
{
private:
	Texture 					*m_brdf_lut;

	std::vector<MeshRenderer *> m_meshes;

	Light						*m_light;
	Shader						*m_shader;
	Camera						*m_camera;
	Cubemap						*m_envMap;

	void bindShader();

public:
	RenderingEngine();
	~RenderingEngine();

	void render();

	inline void setCamera(Camera *camera) { m_camera = camera; }
	inline void setShader(Shader *shader) { m_shader = shader; }
	inline void setLight(Light *light) { m_light = light; }
	inline void setEnvMap(Cubemap *map) { m_envMap = map; }

	inline void addMesh(MeshRenderer *mesh) { m_meshes.push_back(mesh); }
};

#endif
