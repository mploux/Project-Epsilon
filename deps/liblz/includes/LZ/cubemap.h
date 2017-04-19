#ifndef CUBEMAP_H
# define CUBEMAP_H

# define GLEW_STATIC
# include <GL/glew.h>
# include <GLFW/glfw3.h>
# include "texture.h"

namespace lz
{
	class Cubemap
	{
	private:
		GLuint			m_id;
		t_generic_image m_faces[6];

	public:
		Cubemap(const char *paths[6]);
		~Cubemap();

		void bind();
		void unbind();

		inline GLuint getID() { return m_id; }
		inline t_generic_image *getResolution() { return m_faces; }
	};
}

#endif
