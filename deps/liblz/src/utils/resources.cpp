#include "resources.h"

using namespace lz;

std::map<const char *, lz::ObjLoader *> lz::Resources::m_objs;
std::map<const char *, lz::Texture *> lz::Resources::m_textures;

void Resources::clear()
{
	m_objs.clear();
	m_textures.clear();
}

lz::ObjLoader *Resources::loadObj(const char *path)
{
	if(!m_objs[path])
		m_objs[path] = new lz::ObjLoader(path);
	return m_objs[path];
}

lz::Texture *Resources::loadTexture(const char *path)
{
	if(!m_textures[path])
		m_textures[path] = new lz::Texture(path);
	return m_textures[path];
}
