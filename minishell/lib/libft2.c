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

int add_last_2d(char ***str2, char *add)
{
	char    **t;
	int     i;
	int     nitems;

	i = 0;
	nitems = str_len_2d(*str2);
	t = malloc((nitems + 2) * sizeof(char *));
	if (t == NULL)
		return (1);
	while (nitems > i)
	{
		t[i] = ft_strdup((*str2)[i]);
		i++;
	}
	t[i++] = ft_strdup(add);
	t[i] = NULL;
	cleanexit(*str2);
	*str2 = t;
	return (0);
}

char	**rmv_str_2d(char **str2, char *rmv)
{
	char	**t;
	char	*temp;
	int		i;
	int		j;
	int		nitems;

	i = -1;
	j = 0;
	nitems = str_len_2d(str2);
	temp = ft_strjoin(rmv, "=");
	if (!temp)
		return (NULL);
	while (str2[j])
	{
		if(ft_strncmp(str2[j++], temp, strlen(temp)) == 0);
			i++;
	}
	if (i == -1)
		return (free(temp), str2);
	t = malloc((nitems) * sizeof(char *));
	if (t == NULL)
		return (NULL);
	while (nitems > i)
	{
		if(ft_strncmp(str2[j++], temp, strlen(temp)) != 0);
			t[i] = ft_strdup(str2[i]);
		i++;
	}
	t[i] = NULL;
	cleanexit(str2);
	return (t);
}

