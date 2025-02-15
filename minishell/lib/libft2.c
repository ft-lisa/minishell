#include "../minishell.h"

int	ft_isalnum(int c)
{
	if ((c > 64 && c < 91) || (c > 96 && c < 123) || (c > 47 && c < 58))
		return (1);
	else
		return (0);
}

int	str_len_2d(char **str)
{
	int	j;

	j = 0;
	while (str[j])
	{
		j++;
	}
	return (j);
}

char	**strdup_2d(char **s)
{
	char	**t;
	int		i;
	int		j;
	int		nitems;

	i = 0;
	j = 0;
	nitems = str_len_2d(s);
	t = malloc((nitems + 1) * sizeof(char *));
	if (t == NULL)
		return (NULL);
	while (nitems > i)
	{
		t[i] = ft_strdup(s[i]);
		i++;
	}
	t[i] = NULL;
	return (t);
}

char	**add_last_2d(char **str2, char *add)
{
	char	**t;
	int		i;
	int		j;
	int		nitems;

	i = 0;
	j = 0;
	nitems = str_len_2d(str2);
	t = malloc((nitems + 2) * sizeof(char *));
	if (t == NULL)
		return (NULL);
	while (nitems > i)
	{
		t[i] = ft_strdup(str2[i]);
		i++;
	}
	t[i++] = ft_strdup(add);
	t[i] = NULL;
	cleanexit(str2);
	return (t);
}

char	**rmv_str_2d(char **str2, char *rmv)
{
	char	**t;
	int		i;
	int		j;
	int		nitems;

	i = 0;
	j = 0;
	nitems = str_len_2d(str2);
	t = malloc((nitems + 2) * sizeof(char *));
	if (t == NULL)
		return (NULL);
	while (nitems > i)
	{
		t[i] = ft_strdup(str2[i]);
		i++;
	}
	t[i] = NULL;
	cleanexit(str2);
	return (t);
}
