#include "resources.h"

using namespace lz;

std::map<char *, lz::ObjLoader *> lz::Resources::s_objs;

void Resources::clear()
{
	s_objs.clear();
}

lz::ObjLoader *Resources::loadObj(char *path)
{
	if(!s_objs[path])
		s_objs[path] = new lz::ObjLoader(path);
	return s_objs[path];
}
