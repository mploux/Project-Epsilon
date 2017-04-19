#ifndef OBJ_LOADER_H
# define OBJ_LOADER_H

# include <iostream>
# include <vector>
# include "mesh.h"
# include "buffers.h"

namespace lz
{
	typedef struct 	_VertexIndex
	{
		int position;
		int texcoord;
		int normal;
	}				VertexIndex;

	class ObjLoader
	{
	private:
		std::vector<GLfloat> m_loadedPositions;
		std::vector<GLfloat> m_loadedNormals;
		std::vector<GLfloat> m_loadedTexCoords;
		std::vector<VertexIndex> m_loadedIndices;

		int m_positionsSize;
		int m_normalsSize;
		int m_texCoordsSize;
		int m_indicesSize;

		GLfloatBuffer m_positions;
		GLfloatBuffer m_normals;
		GLfloatBuffer m_texCoords;
		GLuintBuffer m_indices;

		Mesh *m_mesh;

	public:
		ObjLoader(const char *path);
		~ObjLoader();

		inline Mesh *getMesh() { return (m_mesh); }
	};
}

#endif
