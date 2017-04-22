#ifndef CUBEMAP_H
# define CUBEMAP_H

# define GLEW_STATIC
# include <GL/glew.h>
# include <GLFW/glfw3.h>
# include "texture.h"
# include "maths.h"
# include "shader.h"
# include "mesh.h"
# include "resources.h"

namespace lz
{
	class Cubemap
	{
	private:
		GLuint			m_id;
		GLuint			m_irradiance_id;
		t_generic_image m_faces[6];

		void generateIrradiance();
		void generateMipmaps();

	public:
		Cubemap(const char *cubemap_paths[6]);
		~Cubemap();

		void bind();
		void unbind();

		inline GLuint getID() { return m_id; }
		inline GLuint getIrradianceID() { return m_irradiance_id; }
		inline t_generic_image *getResolution() { return m_faces; }
	};
}

#endif
