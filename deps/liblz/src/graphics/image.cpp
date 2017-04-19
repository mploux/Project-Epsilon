#include "texture.h"

namespace lz
{
	t_generic_image load_image(const char *path)
	{
		t_generic_image result;
		if (str_has_suffix(path, ".bmp"))
			result = load_bmp(path);
		else if (str_has_suffix(path, ".dds"))
			result = load_dds(path);
		else
		{
			sever("Invalid texture format ! Supported: *.bmp, *.dds");
			exit(-1);
		}
		return (result);
	}
}
