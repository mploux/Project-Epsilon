#include "texture.h"

namespace lz
{
	static FILE *get_bmp_file(const char *path)
	{
		FILE *file;

		printf("loading:%s\n", path);
		file = fopen(path,"rb");
		if (!file)
			printf("%s could not be opened.", path);
		return (file);
	}

	static void set_bmp_header(FILE *file, unsigned char header[54])
	{
		if (fread(header, 1, 54, file) != 54)
			sever("Incorrect BMP file");
		if (header[0]!='B' || header[1] != 'M')
			sever("Incorrect BMP file");
		if (*(int*)&(header[0x1E]) != 0)
			sever("Incorrect BMP file");
		if (*(int*)&(header[0x1C]) != 24)
			sever("Incorrect BMP file");
	}

	t_generic_image load_bmp(const char *path)
	{
		t_generic_image	result;
		unsigned char 	header[54];
		unsigned int 	dataPos;
		unsigned int 	imageSize;
		FILE 			*file;

		file = get_bmp_file(path);
		set_bmp_header(file, header);
		dataPos = *(int*)&(header[0x0A]);
		imageSize = *(int*)&(header[0x22]);
		result.width = *(int*)&(header[0x12]);
		result.height = *(int*)&(header[0x16]);
		if (imageSize == 0)
			imageSize = result.width * result.height * 3;
		if (dataPos == 0)
			dataPos = 54;
		result.data = new unsigned char[imageSize];
		fread(result.data, 1, imageSize, file);
		fclose (file);
		return result;
	}
}
