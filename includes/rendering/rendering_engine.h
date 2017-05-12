#ifndef RENDERING_ENGINE_H
# define RENDERING_ENGINE_H

class RenderingEngine
{
private:
	std::vector<MeshRenderer> m_meshes;

public:
	RenderingEngine();
	~RenderingEngine();
};

#endif
