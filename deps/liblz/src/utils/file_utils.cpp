#include "error.h"
#include "file_utils.h"
#include "string_utils.h"
#include <fcntl.h>
#include <stdlib.h>


char		*lz::load_file(const char *name)
{
	int		fd;
	int		read_size;
	char	read_buff[1024 + 1];
	char	*result;
	char	*tmp;

	fd = 0;
	put_str("loading:");
	put_str(name);
	put_str("\n");
	if (name == NULL || (fd = open(name, O_RDONLY)) == -1)
		sever("unable to load file !");
	result = NULL;
	while ((read_size = read(fd, read_buff, 1024)) != 0)
	{
		tmp = result;
		read_buff[read_size] = '\0';
		result = str_concat(result, read_buff);
		free(tmp);
	}
	return (result);
}
