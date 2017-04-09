#ifndef STRING_UTILS_H
# define STRING_UTILS_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>

void 		put_char(char c);
void		put_str(const char *str);
void		put_nbr(int nb);
int			str_len(const char *str);
char		*str_concat(char *str1, char *str2);
int 		str_count_char(char *str, char split);
char 		**str_split(char *str, char split);
void		str_print_tab(char **tab);
void 		str_clean_tab(char **tab);
int 		str_has_suffix(const char *str, const char *suffix);

#endif
