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
		free(m_image.data);
	}

	void Texture::create_dds_texture(const char *path)
	{
		unsigned int blockSize;
		unsigned int offset;

		offset = 0;
		m_image = load_dds(path);
		glGenTextures(1, &m_id);
		glBindTexture(GL_TEXTURE_2D, m_id);
		glPixelStorei(GL_UNPACK_ALIGNMENT,1);
		blockSize = (m_image.format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
		for (unsigned int level = 0; level < m_image.mipMapCount && (m_image.width || m_image.height); ++level)
		{
			unsigned int size = ((m_image.width+3)/4)*((m_image.height+3)/4)*blockSize;
			glCompressedTexImage2D(GL_TEXTURE_2D, level, m_image.format, m_image.width, m_image.height, 0, size, m_image.data + offset);
			offset += size;
			m_image.width  /= 2;
			m_image.height /= 2;
			if(m_image.width < 1)
				m_image.width = 1;
			if(m_image.height < 1)
				m_image.height = 1;
		}
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -1);
		free(m_image.data);
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
