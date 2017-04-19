#include "cubemap.h"

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
			glCompressedTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, m_faces[i].format, m_faces[i].width, m_faces[i].height, 0, size, m_faces[i].data);
		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
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
