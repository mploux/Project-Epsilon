#ifndef RESOURCES_H
# define RESOURCES_H

# include <map>
# include "obj_loader.h"

namespace lz
{
	class Resources
	{
	private:
		static std::map<char *, lz::ObjLoader *> s_objs;
	public:
		
		static void clear();
		static lz::ObjLoader *loadObj(char *path);
	};
}

#endif