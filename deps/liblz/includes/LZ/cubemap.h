#ifndef CUBEMAP_H
# define CUBEMAP_H

# define GLEW_STATIC
# include <GL/glew.h>
# include <GLFW/glfw3.h>
# include <iostream>
# include "texture.h"
# include "maths.h"
# include "shader.h"
# include "mesh.h"
# include "resources.h"
# include <cmath>

namespace lz
{
	class Cubemap
	{
	private:
		lz::Texture		*m_env_map;
		lz::ObjLoader	*m_cube;
		GLuint			m_id;
		GLuint			m_irradiance_id;
		lz::maths::mat4	m_views[6] =
		{
			lz::maths::mat4::rotate(vec3(1, 0, 0), vec3(0, -1, 0), vec3(0, 0, -1)),
			lz::maths::mat4::rotate(vec3(-1, 0, 0), vec3(0, -1, 0), vec3(0, 0, 1)),
			lz::maths::mat4::rotate(vec3(0, 1, 0), vec3(0, 0, 1), vec3(1, 0, 0)),
			lz::maths::mat4::rotate(vec3(0, -1, 0), vec3(0, 0, -1), vec3(1, 0, 0)),
			lz::maths::mat4::rotate(vec3(0, 0, 1), vec3(0, -1, 0), vec3(1, 0, 0)),
			lz::maths::mat4::rotate(vec3(0, 0, -1), vec3(0, -1, 0), vec3(-1, 0, 0))
		};

		void generateIrradiance();
		void generateMipmaps(int size);

	public:
		Cubemap(const char *path, int size);
		~Cubemap();

		void bind();
		void unbind();

		inline GLuint getID() { return m_id; }
		inline GLuint getIrradianceID() { return m_irradiance_id; }
	};
}

#endif
