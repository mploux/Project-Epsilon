#ifndef ERROR_H
# define ERROR_H

# include <unistd.h>
# include <stdlib.h>

namespace lz
{
	int error(const char *error);
	int sever(const char *sever);
}

#endif
