#ifndef SKYBOX_H
# define SKYBOX_H

# include <LZ/cubemap.h>
# include <LZ/mesh.h>
# include <LZ/shader.h>
# include <LZ/camera.h>

class Skybox
{
private:
	lz::Cubemap *m_cubemap;
	lz::Mesh	*m_cube;
	lz::Shader	*m_shader;


	void generateCubeMesh();
public:
	Skybox(lz::Cubemap *cubemap);
	~Skybox();

	void render(lz::Camera *camera);
};

#endif
