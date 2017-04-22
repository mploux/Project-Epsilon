#include "cubemap.h"

using namespace lz::maths;

namespace lz
{
	Cubemap::Cubemap(const char *paths[6])
	{
		glGenTextures(1, &m_id);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_id);
		glPixelStorei(GL_UNPACK_ALIGNMENT,1);
		for (int i = 0; i < 6; i++)
		{
			m_faces[i] = load_image(paths[i]);
			unsigned int blockSize = (m_faces[i].format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
			unsigned int size = ((m_faces[i].width+3)/4)*((m_faces[i].height+3)/4)*blockSize;
			glCompressedTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, m_faces[i].format,
					m_faces[i].width, m_faces[i].height, 0, size, m_faces[i].data);
		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		Cubemap::generateIrradiance();
	}

	void Cubemap::generateIrradiance()
	{
		GLuint fbo, rbo;
		Shader shader = lz::Shader("data/shaders/cubemap_irradiance_v.glsl", "data/shaders/cubemap_irradiance_f.glsl");
		lz::Mesh *cube = lz::Resources::loadObj("data/models/Cube.obj")->getMesh();
		mat4 views[] =
		{
			mat4::rotate(vec3(1, 0, 0), vec3(0, -1, 0), vec3(0, 0, -1)),
			mat4::rotate(vec3(-1, 0, 0), vec3(0, -1, 0), vec3(0, 0, 1)),
			mat4::rotate(vec3(0, 1, 0), vec3(0, 0, 1), vec3(1, 0, 0)),
			mat4::rotate(vec3(0, -1, 0), vec3(0, 0, -1), vec3(1, 0, 0)),
			mat4::rotate(vec3(0, 0, 1), vec3(0, -1, 0), vec3(1, 0, 0)),
			mat4::rotate(vec3(0, 0, -1), vec3(0, -1, 0), vec3(-1, 0, 0))
		};
		glGenTextures(1, &m_irradiance_id);
		glGenFramebuffers(1, &fbo);
		glGenRenderbuffers(1, &rbo);
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		glBindRenderbuffer(GL_RENDERBUFFER, rbo);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 512, 512);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_irradiance_id);
		for (unsigned int i = 0; i < 6; ++i)
		    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, 512, 512, 0, GL_RGB, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		shader.bind();
		glActiveTexture(GL_TEXTURE0);
		Cubemap::bind();
		shader.setUniform("projectionMatrix", mat4::perspective(90.0, 1.0, 0.1, 2.0));
		shader.setUniform("env_map", 0);
		glViewport(0, 0, 512, 512);
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		for (int i = 0; i < 6; i++)
		{
			shader.setUniform("modelMatrix", views[i]);
			shader.setUniform("viewMatrix", mat4::identity());
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, m_irradiance_id, 0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			cube->draw();
		}
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	Cubemap::~Cubemap()
	{}

	void Cubemap::bind()
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_id);
	}

	void Cubemap::unbind()
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}
}
