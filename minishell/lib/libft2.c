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

int	isin_2d(char **str, char *check)
{
	int	j;
	int	count;
	char 	*temp;

	j = 0;
	count = 0;
	temp = ft_strjoin(check, "=");
	if (!temp)
		return (1);
	while (str[j])
	{
		if(ft_strncmp(str[j++], temp, strlen(temp)) == 0)
			count++;
	}
	if (count == 0)
		return (free(temp), 0);
	free(temp);
	return (1);
}

int add_last_2d(char ***str2, char *add)
{
	char    **t;
	int     i;
	int     nitems;
	char	*temp;

	i = 0;
	temp = copy_until(add, '=');
	if (!temp)
		return (1);
	if (isin_2d((*str2), temp) == 1)
		rmv_str_2d(str2, temp);
	nitems = str_len_2d(*str2);
	t = malloc((nitems + 2) * sizeof(char *));
	if (t == NULL)
		return (free(temp), 1);
	while (nitems > i)
	{
		t[i] = ft_strdup((*str2)[i]);
		i++;
	}
	t[i++] = ft_strdup(add);
	t[i] = NULL;
	cleanexit(*str2);
	*str2 = t;
	return (free(temp), 0);
}

char	*copy_until(char *str, char c)
{
	int	i;
	int	size;
	char	*new;

	i = 0;
	size = 0;
	while (str[size])
		if (str[size++] == c)
			break;
	if (str[size] == '\0')
		return (ft_strdup(str));
	size--;
	new = malloc((size + 1) * sizeof(char));
	if (!new)
		return (NULL);
	while (i < size)
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

int	rmv_str_2d(char ***str2, char *rmv)
{
	char	**t;
	char	*temp;
	int		i;
	int		j;
	int		nitems;

	j = 0;
	nitems = str_len_2d(*str2);
	if (!rmv)
		return (0);
	temp = ft_strjoin(rmv, "=");
	if (!temp)
		return (1);
	if (isin_2d((*str2), rmv) == 0)
		return (free(temp), 0);
	t = malloc((nitems) * sizeof(char *));
	if (t == NULL)
		return (1);
	j = 0;
	i = 0;
	while ((*str2)[j])
	{
		if(ft_strncmp((*str2)[j], temp, strlen(temp)) != 0)
			t[i++] = ft_strdup((*str2)[j]);
		j++;
	}
	t[i] = NULL;
	cleanexit(*str2);
	*str2 = t;
	free(temp);
	return (0);
}

