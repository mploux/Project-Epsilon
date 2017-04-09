#include "texture.h"

namespace lz
{
	Texture::Texture(const char *path)
	{
		if (str_has_suffix(path, ".bmp"))
			create_bmp_texture(path);
		else if (str_has_suffix(path, ".dds"))
			create_dds_texture(path);
		else
			sever("Invalid texture format ! Supported: *.bmp, *.dds");
	}

	Texture::~Texture()
	{}

	void Texture::create_bmp_texture(const char *path)
	{
		m_image = load_bmp(path);
		glGenTextures(1, &m_id);
		glBindTexture(GL_TEXTURE_2D, m_id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_image.width, m_image.height, 0, GL_BGR, GL_UNSIGNED_BYTE, m_image.data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	void Texture::create_dds_texture(const char *path)
	{
		(void) path;
	}

	void Texture::bind()
	{
		glBindTexture(GL_TEXTURE_2D, m_id);
	}

	void Texture::unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}
