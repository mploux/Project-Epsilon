#include "obj_loader.h"
#include "error.h"
#include "string_utils.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string_utils.h"

using namespace lz;
using namespace maths;

ObjLoader::ObjLoader(const char *path)
{
	char line[256];
	FILE *fp;

	m_positionsSize = 0;
	m_normalsSize = 0;
	m_texCoordsSize = 0;
	m_indicesSize = 0;
	printf("loading:%s\n", path);
	if ((fp = fopen(path, "r")) == NULL)
		sever("Unable to load file !");
	while (fgets(line, 256, fp))
	{
		char **tokens = str_split(line, ' ');
		if (strcmp(tokens[0], "v") == 0)
		{
			m_loadedPositions.push_back((GLfloat) atof(tokens[1]));
			m_loadedPositions.push_back((GLfloat) atof(tokens[2]));
			m_loadedPositions.push_back((GLfloat) atof(tokens[3]));
			m_positionsSize++;
		}
		else if (strcmp(tokens[0], "vn") == 0)
		{
			m_loadedNormals.push_back((GLfloat) atof(tokens[1]));
			m_loadedNormals.push_back((GLfloat) atof(tokens[2]));
			m_loadedNormals.push_back((GLfloat) atof(tokens[3]));
			m_normalsSize++;
		}
		else if (strcmp(tokens[0], "vt") == 0)
		{
			m_loadedTexCoords.push_back((GLfloat) atof(tokens[1]));
			m_loadedTexCoords.push_back((GLfloat) atof(tokens[2]));
			m_texCoordsSize++;
		}
		else if (strcmp(tokens[0], "f") == 0)
		{
			char **indides_a = str_split(tokens[1], '/');
			char **indides_b = str_split(tokens[2], '/');
			char **indides_c = str_split(tokens[3], '/');

			int p1 = atoi(indides_a[0]) - 1;
			free(indides_a[0]);
			int t1 = atoi(indides_a[1]) - 1;
			free(indides_a[1]);
			int n1 = atoi(indides_a[2]) - 1;
			free(indides_a[2]);
			free(indides_a);

			int p2 = atoi(indides_b[0]) - 1;
			free(indides_b[0]);
			int t2 = atoi(indides_b[1]) - 1;
			free(indides_b[1]);
			int n2 = atoi(indides_b[2]) - 1;
			free(indides_b[2]);
			free(indides_b);

			int p3 = atoi(indides_c[0]) - 1;
			free(indides_c[0]);
			int t3 = atoi(indides_c[1]) - 1;
			free(indides_c[1]);
			int n3 = atoi(indides_c[2]) - 1;
			free(indides_c[2]);
			free(indides_c);

			VertexIndex a = {p1, t1, n1};
			VertexIndex b = {p2, t2, n2};
			VertexIndex c = {p3, t3, n3};

			m_loadedIndices.push_back(a);
			m_loadedIndices.push_back(b);
			m_loadedIndices.push_back(c);

			m_indicesSize += 3;
		}
	}
	fclose(fp);
	m_positions.size = sizeof(GLfloat) * m_indicesSize * 3;
	m_positions.buffer = (GLfloat *)malloc(m_positions.size);
	if (m_positions.buffer == NULL)
		printf("OBJ POSITION MALLOC PROBLEM !");
	m_normals.size = sizeof(GLfloat) * m_indicesSize * 3;
	m_normals.buffer = (GLfloat *)malloc(m_normals.size);
	if (m_normals.buffer == NULL)
		printf("OBJ NORMALS MALLOC PROBLEM !");
	m_texCoords.size = sizeof(GLfloat) * m_indicesSize * 2;
	m_texCoords.buffer = (GLfloat *)malloc(m_texCoords.size);
	if (m_texCoords.buffer == NULL)
		printf("OBJ TEX COORDS MALLOC PROBLEM !");
	m_tangents.size = sizeof(GLfloat) * m_indicesSize * 3;
	m_tangents.buffer = (GLfloat *)malloc(m_tangents.size);
	if (m_tangents.buffer == NULL)
		printf("OBJ TANGENTS MALLOC PROBLEM !");
	m_indices.size = sizeof(GLuint) * m_indicesSize;
	m_indices.buffer = (GLuint *)malloc(m_indices.size);
	if (m_indices.buffer == NULL)
		printf("OBJ INDICES MALLOC PROBLEM !");

	for (int i = 0; i < m_indicesSize; i++)
	{
		VertexIndex index = m_loadedIndices[i];
		m_positions.buffer[i * 3 + 0] = m_loadedPositions[index.position * 3 + 0];
		m_positions.buffer[i * 3 + 1] = m_loadedPositions[index.position * 3 + 1];
		m_positions.buffer[i * 3 + 2] = m_loadedPositions[index.position * 3 + 2];

		m_normals.buffer[i * 3 + 0] = m_loadedNormals[index.normal * 3 + 0];
		m_normals.buffer[i * 3 + 1] = m_loadedNormals[index.normal * 3 + 1];
		m_normals.buffer[i * 3 + 2] = m_loadedNormals[index.normal * 3 + 2];

		m_texCoords.buffer[i * 2 + 0] = m_loadedTexCoords[index.texcoord * 2 + 0];
		m_texCoords.buffer[i * 2 + 1] = m_loadedTexCoords[index.texcoord * 2 + 1];

		m_indices.buffer[i] = i;
	}
	for (int i = 0; i < m_indicesSize; i += 3)
	{
		ObjLoader::calcTangent(i,
			m_loadedIndices[i],
			m_loadedIndices[i + 1],
			m_loadedIndices[i + 2]
		);
	}
	m_mesh = new Mesh(m_indicesSize);
	m_mesh->setPositions(m_positions);
	m_mesh->setNormals(m_normals);
	m_mesh->setTexCoords(m_texCoords);
	m_mesh->setTangents(m_tangents);
	m_mesh->setIndices(m_indices);
	m_mesh->create();
}

void ObjLoader::calcTangent(int index, VertexIndex i0, VertexIndex i1, VertexIndex i2)
{
	vec3 edge1 = vec3(
		m_loadedPositions[i1.position * 3 + 0] - m_loadedPositions[i0.position * 3 + 0],
		m_loadedPositions[i1.position * 3 + 1] - m_loadedPositions[i0.position * 3 + 1],
		m_loadedPositions[i1.position * 3 + 2] - m_loadedPositions[i0.position * 3 + 2]
	);
	vec3 edge2 = vec3(
		m_loadedPositions[i2.position * 3 + 0] - m_loadedPositions[i0.position * 3 + 0],
		m_loadedPositions[i2.position * 3 + 1] - m_loadedPositions[i0.position * 3 + 1],
		m_loadedPositions[i2.position * 3 + 2] - m_loadedPositions[i0.position * 3 + 2]
	);

	float deltaU1 = m_loadedTexCoords[i1.texcoord * 2 + 0] - m_loadedTexCoords[i0.texcoord * 2 + 0];
	float deltaV1 = m_loadedTexCoords[i1.texcoord * 2 + 1] - m_loadedTexCoords[i0.texcoord * 2 + 1];
	float deltaU2 = m_loadedTexCoords[i2.texcoord * 2 + 0] - m_loadedTexCoords[i0.texcoord * 2 + 0];
	float deltaV2 = m_loadedTexCoords[i2.texcoord * 2 + 1] - m_loadedTexCoords[i0.texcoord * 2 + 1];

	float f = 1.0f / (deltaU1 * deltaV2 - deltaU2 * deltaV1);
	vec3 tangent = vec3(
		f * (deltaV2 * edge1.x - deltaV1 * edge2.x),
		f * (deltaV2 * edge1.y - deltaV1 * edge2.y),
		f * (deltaV2 * edge1.z - deltaV1 * edge2.z)
	).normalize();
	m_tangents.buffer[index * 3 + 0] = tangent.x;
	m_tangents.buffer[index * 3 + 1] = tangent.y;
	m_tangents.buffer[index * 3 + 2] = tangent.z;
}

ObjLoader::~ObjLoader()
{
	free(m_positions.buffer);
	free(m_normals.buffer);
	free(m_indices.buffer);
	delete m_mesh;
}
