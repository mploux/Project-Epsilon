#ifndef TEXTURE_H
# define TEXTURE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

# define GLEW_STATIC
# include <GL/glew.h>
# include <GLFW/glfw3.h>

# include "error.h"
#include "string_utils.h"

namespace lz
{
	typedef struct	s_generic_image
	{
		unsigned int	width;
		unsigned int	height;
		unsigned char	*data;
	}				t_generic_image;

	t_generic_image load_bmp(const char *path);

	class Texture
	{
	private:
		GLuint			m_id;
		t_generic_image m_image;

		void create_bmp_texture(const char *path);
		void create_dds_texture(const char *path);
	public:
		Texture(const char *path);
		~Texture();

		void bind();
		void unbind();

		inline t_generic_image getImage() { return m_image; }
	};
}

#endif
