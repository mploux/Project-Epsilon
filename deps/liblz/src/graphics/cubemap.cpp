#include "cubemap.h"

using namespace lz::maths;

namespace lz
{
	Cubemap::Cubemap(const char *path, int size)
	{
		m_env_map = lz::Resources::loadTexture(path);
		// TODO: generate a cube primitive 
		m_cube = lz::Resources::loadObj("data/models/Cube.obj");
		Cubemap::generateMipmaps(size);
		Cubemap::generateIrradiance();
	}

	void Cubemap::generateMipmaps(int size)
	{
		GLuint fbo, rbo;
		Shader shader = lz::Shader("data/shaders/cubemap_v.glsl", "data/shaders/cubemap_f.glsl");

		glGenTextures(1, &m_id);
		glGenFramebuffers(1, &fbo);
		glGenRenderbuffers(1, &rbo);
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		glBindRenderbuffer(GL_RENDERBUFFER, rbo);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_id);
		for (unsigned int i = 0; i < 6; ++i)
		    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, size, size, 0, GL_RGB, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
		shader.bind();
		glActiveTexture(GL_TEXTURE0);
		shader.setUniform("env_map", 0);
		m_env_map->bind();
		shader.setUniform("projectionMatrix", mat4::perspective(90.0, 1.0, 0.1, 2.0));
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		for (int mip = 0; mip < 5; mip++)
		{
			int mip_size = size * std::pow(0.5, mip);
			GLfloat roughness = mip / 4.0;
			shader.setUniform("roughness", roughness);
			glViewport(0, 0, mip_size, mip_size);
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, mip_size, mip_size);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo);
			for (int i = 0; i < 6; i++)
			{
				shader.setUniform("modelMatrix", m_views[i]);
				shader.setUniform("viewMatrix", mat4::identity());
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, m_id, mip);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				m_cube->getMesh()->draw();
			}
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void Cubemap::generateIrradiance()
	{
		GLuint fbo, rbo;
		Shader shader = lz::Shader("data/shaders/cubemap_irradiance_v.glsl", "data/shaders/cubemap_irradiance_f.glsl");

		glGenTextures(1, &m_irradiance_id);
		glGenFramebuffers(1, &fbo);
		glGenRenderbuffers(1, &rbo);
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		glBindRenderbuffer(GL_RENDERBUFFER, rbo);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 24, 24);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_irradiance_id);
		for (unsigned int i = 0; i < 6; ++i)
		    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, 24, 24, 0, GL_RGB, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
		shader.bind();
		glActiveTexture(GL_TEXTURE0);
		m_env_map->bind();
		shader.setUniform("projectionMatrix", mat4::perspective(90.0, 1.0, 0.1, 2.0));
		shader.setUniform("env_map", 0);
		glViewport(0, 0, 24, 24);
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		for (int i = 0; i < 6; i++)
		{
			shader.setUniform("modelMatrix", m_views[i]);
			shader.setUniform("viewMatrix", mat4::identity());
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, m_irradiance_id, 0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			m_cube->getMesh()->draw();
		}
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	Cubemap::~Cubemap()
	{
		delete m_env_map;
		delete m_cube;
	}

	void Cubemap::bind()
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_id);
	}

	void Cubemap::unbind()
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}
}
