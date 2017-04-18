#ifndef RESOURCES_H
# define RESOURCES_H

# include <map>
# include "obj_loader.h"
# include "texture.h"

namespace lz
{
	class Resources
	{
	private:
		static std::map<char *, lz::ObjLoader *> m_objs;
		static std::map<char *, lz::Texture *> m_textures;

	public:
		static void clear();
		static lz::ObjLoader *loadObj(char *path);
		static lz::Texture *loadTexture(char *path);
	};
}

#endif
