#include "../minishell.h"

static int	splitlen(char const *s1, char c1)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (s1[i] != '\0')
	{
		while (s1[i] == c1 && s1[i])
			i++;
		if (s1[i])
			k++;
		while (s1[i] != c1 && s1[i])
			i++;
	}
	return (k);
}


static char	*t2f(char const *s, int start_s, char c)
{
	int		i;
	int		len_s;
	char	*t2;

	i = start_s;
	while (s[i] != c && s[i])
		i++;
	len_s = i - start_s;
	i = 0;
	t2 = malloc((len_s + 1) * sizeof(char));
	if (t2 == NULL)
		return (NULL);
	while (i < len_s)
	{
		t2[i] = s[start_s + i];
		i++;
	}
	t2[i] = '\0';
	return (t2);
}

char	**ft_split(char const *s, char c)
{
	char	**t1;
	int		i;
	int		j;

	t1 = malloc((splitlen(s, c) + 1) * sizeof(char *));
	if (t1 == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (!s[i])
			break ;
		t1[j] = t2f(s, i, c);
		if (t1[j++] == NULL)
			return (cleanexit(t1));
		while (s[i] != c && s[i])
			i++;
	}
	t1[j] = NULL;
	return (t1);
}
