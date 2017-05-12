#include <iostream>
#include "texture.h"
#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

namespace lz
{

	static FILE *load_dds_file(const char *path)
	{
		FILE *result;

		result = fopen(path, "rb");
		if (result == NULL)
		{
			std::cout << "ERROR: Unable to load texture: " << path << std::endl;
			exit(-1);
		}
		char filecode[4];
		fread(filecode, 1, 4, result);
		if (strncmp(filecode, "DDS ", 4) != 0)
		{
			fclose(result);
			return 0;
		}
		return (result);
	}

	static int get_dds_format(int four_cc)
	{
		if (four_cc == FOURCC_DXT1)
			return (GL_COMPRESSED_RGBA_S3TC_DXT1_EXT);
		if (four_cc == FOURCC_DXT3)
			return (GL_COMPRESSED_RGBA_S3TC_DXT3_EXT);
		if (four_cc == FOURCC_DXT5)
			return (GL_COMPRESSED_RGBA_S3TC_DXT5_EXT);
		return (0);
	}

	t_generic_image load_dds(const char *path)
	{
		t_generic_image result;
		unsigned int linearSize;
		unsigned char header[124];
		FILE *fp;

		printf("loading:%s\n", path);
		fp = load_dds_file(path);
		fread(&header, 124, 1, fp);
		result.height = *(unsigned int*)&(header[8 ]);
		result.width = *(unsigned int*)&(header[12]);
		linearSize = *(unsigned int*)&(header[16]);
		result.mipMapCount = *(unsigned int*)&(header[24]);
		result.data_size = result.mipMapCount > 1 ? linearSize * 2 : linearSize;
		result.data = new unsigned char[result.data_size];
		result.format = get_dds_format(*(unsigned int*)&(header[80]));
		fread(result.data, 1, result.data_size, fp);
		fclose(fp);
		return (result);
	}
}
