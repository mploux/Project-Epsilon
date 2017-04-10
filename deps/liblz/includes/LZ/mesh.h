#ifndef MESH_H
# define MESH_H

# include <stdlib.h>
# include <GL/glew.h>
# include <iostream>
# include <vector>
# include "maths.h"
# include "buffers.h"

using namespace lz::maths;

namespace lz
{
	class Mesh
	{
	private:
		GLuint  m_vao, m_vbo, m_nbo, m_tbo, m_ibo;

		GLfloatBuffer 	m_positions;
		GLfloatBuffer 	m_texCoords;
		GLfloatBuffer 	m_normals;
		GLfloatBuffer 	m_tangents;
		GLuintBuffer 	m_indices;

		int 			m_size;

	public:
		Mesh(int size);
		~Mesh();

		void create();
		void draw();

		inline void setPositions(GLfloatBuffer positions) { m_positions = positions; }
		inline void setTexCoords(GLfloatBuffer texCoords) { m_texCoords = texCoords; }
		inline void setNormals(GLfloatBuffer normals) { m_normals = normals; }
		inline void setTangents(GLfloatBuffer tangents) { m_tangents = tangents; }
		inline void setIndices(GLuintBuffer indices) { m_indices = indices; }

		inline GLfloatBuffer getPositions() { return (m_positions); }
		inline GLfloatBuffer getTexCoords() { return (m_texCoords); }
		inline GLfloatBuffer getNormals() { return (m_normals); }
		inline GLfloatBuffer getTangents() { return (m_tangents); }
		inline GLuintBuffer  getIndices() { return (m_indices); }
	};
}

#endif
