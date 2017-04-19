#include <GL/glew.h>
#include <iostream>
#include <vector>
#include "shader.h"
#include "error.h"
#include "file_utils.h"

using namespace lz;

Shader::Shader(const char *vertex_path, const char *fragment_path)
{
	const char *vertex_source = load_file(vertex_path);
	const char *fragment_source = load_file(fragment_path);
	m_program = Shader::createProgram(vertex_source, fragment_source);
}

Shader::~Shader()
{
	glDeleteProgram(m_program);
}

GLuint Shader::createProgram(const char *vertex_source, const char *fragment_source)
{
	GLuint program = glCreateProgram();

	if (program == GL_FALSE)
		sever("Unable to create shader program !");

	GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

	GLuint vertex_shader = Shader::createShader(vertex_source, GL_VERTEX_SHADER);
	GLuint fragment_shader = Shader::createShader(fragment_source, GL_FRAGMENT_SHADER);

	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);

	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vertex);
	glDeleteShader(fragment);

	return (program);
}

GLuint Shader::getUniformLocation(const char *name)
{
	return glGetUniformLocation(m_program, (GLchar*)name);
}

void Shader::setUniform(const char *name, GLint v)
{
	glUniform1i(getUniformLocation(name), v);
}

void Shader::setUniform(const char *name, GLfloat v)
{
	glUniform1f(getUniformLocation(name), v);
}

void Shader::setUniform(const char *name, vec3 v)
{
	glUniform3f(getUniformLocation(name), v.x, v.y, v.z);
}

void Shader::setUniform(const char *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	glUniform4f(getUniformLocation(name), x, y, z, w);
}

void Shader::setUniform(const char *name, mat4 m)
{
	glUniformMatrix4fv(getUniformLocation(name), 1, false, m.m_matrix);
}

GLuint Shader::createShader(const char *source, int type)
{
	GLuint shader;
	GLint result;

	shader = glCreateShader(type);
	if (shader == GL_FALSE)
		sever("Unable to create shader !");
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		GLint length;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		std::vector<char> error(length);
		glGetShaderInfoLog(shader, length, &length, &error[0]);
		std::cout << &error[0] << std::endl;
		glDeleteShader(shader);
		return (0);
	}
	return (shader);
}
