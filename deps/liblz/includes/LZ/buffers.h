#ifndef BUFFER_H
# define BUFFER_H

# include <GL/glew.h>

namespace lz
{
	typedef struct 	_GLfloatBuffer
	{
		int 		size;
		GLfloat 	*buffer;
	}				GLfloatBuffer;

	typedef struct 	_GLuintBuffer
	{
		int 		size;
		GLuint	 	*buffer;
	}				GLuintBuffer;
}

#endif
