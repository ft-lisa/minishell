#include "../minishell.h"

size_t	ft_strlen(const char *c)
{
	size_t	i;

	i = 0;
	while (c[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, const char *s2)
{
	char	*t;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	t = malloc((ft_strlen(s1) + ft_strlen(s2)) * sizeof(char) + 1);
	if (t == NULL)
		return (NULL);
	while (s1[i])
	{
		t[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		t[i + j] = s2[j];
		j++;
	}
	t[i + j] = '\0';
	return (t);
}

void	*ft_calloc(size_t nitems, size_t size)
{
	unsigned char	*t;
	size_t			i;
	size_t			k;

	i = 0;
	if (size != 0 && (nitems * size) / size != nitems)
		return (NULL);
	k = nitems * size;
	t = malloc(k);
	if (!t)
		return (NULL);
	while (nitems * size > i)
	{
		t[i] = 0;
		i++;
	}
	return (t);
}

char	*ft_strdup(const char *s)
{
	char	*t;
	size_t	i;
	size_t	nitems;

	i = 0;
	nitems = ft_strlen(s);
	t = malloc(nitems * sizeof(char) + 1);
	if (t == NULL)
		return (NULL);
	while (nitems > i)
	{
		t[i] = s[i];
		i++;
	}
	t[i] = '\0';
	return (t);
}
