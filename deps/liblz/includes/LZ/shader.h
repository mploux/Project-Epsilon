#ifndef SHADER_H
# define SHADER_H

# include "gl_utils.h"
# include "maths.h"

namespace lz
{
	using namespace maths;

	class Shader
	{
	private:
		GLuint	m_program;

		GLuint	createProgram(const char *vertex_source, const char *fragment_source);
		GLuint	createShader(const char *source, int shader);

		GLuint 	getUniformLocation(const char *name);

	public:
		Shader(const char *vertex_path, const char *fragment_path);
		~Shader();

		void 	setUniform(const char *name, GLint v);
		void 	setUniform(const char *name, GLfloat v);
		void 	setUniform(const char *name, vec3 v);
		void 	setUniform(const char *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
		void 	setUniform(const char *name, mat4 v);

		inline void bind() { glUseProgram(m_program); };
		inline void unbind() { glUseProgram(0); };

		inline int getProgram() { return (m_program); }
	};
}
#endif
