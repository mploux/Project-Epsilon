#include "string_utils.h"

void 		put_char(char c)
{
	write(1, &c, 1);
}

void		put_str(const char *str)
{
	write(1, str, str_len(str));
}

void		put_nbr(int nb)
{
	long n;

	n = nb;
	if (n < 0)
	{
		n *= -1;
		put_char('-');
	}
	if (n < 10)
	{
		put_char(n + '0');
	}
	if (n >= 10)
	{
		put_nbr(n / 10);
		put_nbr(n % 10);
	}
}

int			str_len(const char *str)
{
	int		i;

	i = -1;
	if (str == NULL)
		return (0);
	while (str && str[++i]);
	return (i);
}

char		*str_concat(char *str1, char *str2)
{
	int		ln1;
	int		ln2;
	int		i;
	int		j;
	char	*result;

	ln1 = str_len(str1);
	ln2 = str_len(str2);
	i = 0;
	j = 0;
	if ((result = (char *)malloc(sizeof(char) * (ln1 + ln2 + 1))) == NULL)
		return (NULL);
	result[ln1 + ln2] = '\0';
	while (i < ln1)
	{
		result[i] = str1[i];
		i++;
	}
	while (j < ln2)
	{
		result[i + j] = str2[j];
		j++;
	}
	return (result);
}

static char		*getword(const char *s, char c, int i)
{
	int		j;
	char	*result;

	j = 0;
	while (s[i + j] != c && s[i + j] != 0)
		j++;
	if (!(result = (char *)malloc(sizeof(char) * (j + 1))))
		return (NULL);
	j = 0;
	while ((s[i + j] != c && s[i + j] != 0))
	{
		result[j] = s[i + j];
		j++;
	}
	result[j] = 0;
	j = 0;
	return (result);
}

static char		**malloc_words(const char *s, char c)
{
	int		i;
	int		num;
	char	**result;

	i = 0;
	num = 1;
	if (!s)
		return (NULL);
	while (s[i++])
		if (s[i - 1] != c && (s[i] == c || s[i] == 0))
			num++;
	if (!(result = (char **)malloc(sizeof(char *) * num)))
		return (NULL);
	return (result);
}

char			**str_split(char *s, char c)
{
	int		i;
	int		k;
	char	**result;

	i = 0;
	k = 0;
	if (!(result = malloc_words(s, c)))
		return (NULL);
	while (s[i])
	{
		if (s[i] != c && (s[i - 1] == c || i == 0))
			result[k++] = getword(s, c, i);
		result[k] = NULL;
		i++;
	}
	if (!i)
		result[0] = NULL;
	return (result);
}

void		str_print_tab(char **tab)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (tab[i])
	{
		while (tab[i][j])
		{
			put_char(tab[i][j]);
			j++;
		}
		put_char('\n');
		j = 0;
		i++;
	}
}

void 		str_clean_tab(char **tab)
{
	int i;

	i = 0;
	while(tab[i++])
		free(tab[i - 1]);
	free(tab);
}

int str_has_suffix(const char *str, const char *suffix)
{
    if (!str || !suffix)
        return 0;
    size_t lenstr = str_len(str);
    size_t lensuffix = str_len(suffix);
    if (lensuffix >  lenstr)
        return 0;
    return strncmp(str + lenstr - lensuffix, suffix, lensuffix) == 0;
}
