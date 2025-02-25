// #include "minishell.h"

// size_t	ft_strlen(const char *c)
// {
// 	size_t	i;

// 	i = 0;
// 	while (c[i] != '\0')
// 		i++;
// 	return (i);
// }

// int	isin(char *s, char c)
// {
// 	int	i;

// 	i = 0;
// 	while (s[i])
// 	{
// 		if (s[i] == c)
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

// int	ft_strncmp(const char *s1, const char *s2, size_t n)
// {
// 	unsigned int	j;
// 	unsigned int	i;

// 	if (n == 0)
// 		return (0);
// 	i = 0;
// 	j = 0;
// 	while (s1[i] != '\0' && s1[i] == s2[i] && i < n - 1)
// 		i++;
// 	j = (unsigned char)s1[i] - (unsigned char)s2[i];
// 	return (j);
// }

// char	*ft_strdup(const char *s)
// {
// 	char	*t;
// 	size_t	i;
// 	size_t	nitems;

// 	i = 0;
// 	nitems = ft_strlen(s);
// 	t = malloc(nitems * sizeof(char) + 1);
// 	if (t == NULL)
// 		return (NULL);
// 	while (nitems > i)
// 	{
// 		t[i] = s[i];
// 		i++;
// 	}
// 	t[i] = '\0';
// 	return (t);
// }

// char	*ft_strjoin(char const *s1, const char *s2)
// {
// 	char	*t;
// 	size_t	i;
// 	size_t	j;

// 	i = 0;
// 	j = 0;
// 	t = malloc((ft_strlen(s1) + ft_strlen(s2)) * sizeof(char) + 1);
// 	if (t == NULL)
// 		return (NULL);
// 	while (s1[i])
// 	{
// 		t[i] = s1[i];
// 		i++;
// 	}
// 	while (s2[j])
// 	{
// 		t[i + j] = s2[j];
// 		j++;
// 	}
// 	t[i + j] = '\0';
// 	return (t);
// }

// char	*get_path_var(char *envp[], char *p1)
// {
// 	int		i;
// 	int		j;
//         int             len_p1;

// 	i = 0;
//         len_p1 = ft_strlen(p1);
// 	while (envp[i])
// 	{
// 		j = 0;
// 		while (envp[i][j] && envp[i][j] == p1[j])
// 			j++;
// 		if (j == len_p1 && envp[i][j] == '=')
// 		{
// 			return (envp[i] + j + 1);
// 		}
// 		i++;
// 	}
// 	return (NULL);
// }

// int	isin_2d_equal(char **str, char *check)
// {
// 	int	j;
// 	int	count;
// 	char 	*temp;

// 	j = 0;
// 	count = 0;
// 	temp = ft_strjoin(check, "=");
// 	if (!temp)
// 		return (1);
// 	while (str[j])
// 	{
// 		if(ft_strncmp(str[j++], temp, strlen(temp)) == 0)
// 			count++;
// 	}
// 	if (count == 0)
// 		return (free(temp), 0);
// 	free(temp);
// 	return (1);
// }

// int	ft_isalnum(int c)
// {
// 	if ((c > 64 && c < 91) || (c > 96 && c < 123) || (c > 47 && c < 58))
// 		return (1);
// 	else
// 		return (0);
// }


// char	*copy_until_alnum_under(char *str)
// {
// 	int	i;
// 	int	size;
// 	char	*new;

// 	i = 0;
// 	size = 0;
// 	while (str[size])
// 		if (ft_isalnum(str[size]) == 0 || str[size] == '_')
// 			break;
// 	if (str[size] == '\0')
// 		return (ft_strdup(str));
// 	size--;
// 	new = malloc((size + 1) * sizeof(char));
// 	if (!new)
// 		return (NULL);
// 	while (i < size)
// 	{
// 		new[i] = str[i];
// 		i++;
// 	}
// 	new[i] = '\0';
// 	return (new);
// }

// int	replace_str(char **mainstr, char *before, char *after, int index)
// {
// 	char	*new;
// 	int	i;
// 	int	len_a;
// 	int	len_b;

// 	i = 0;
// 	len_a = 0;
// 	if (after)
// 		len_a = ft_strlen(after);
// 	if (before == NULL)
// 		return (-1);
// 	len_b = ft_strlen(before);
// 	new = malloc ((ft_strlen((*mainstr)) - len_b + len_a  + 1) * sizeof(char));
// 	if (!new)
// 		return (-1);
// 	while(i < index)
// 	{
// 		new[i] = (*mainstr)[i];
// 		i++;
// 	}
// 	i = 0;
// 	while(after[i])
// 	{
// 		new[index + i] = after[i];
// 		i++;
// 	}
// 	while((*mainstr)[index + len_b])
// 	{
// 		new[index + len_a] = (*mainstr)[index + len_b];
// 		index++;
// 	}
// 	new[index + len_a] = '\0';
// 	free(*mainstr);
// 	*mainstr = new;
// 	return (0);
// }

// int	expand(char **cmd, char **env)
// {
// 	char	*new;
// 	char	*temp;
// 	char	*temp2;
// 	int	i;

// 	i = 0;
// 	while ((*cmd)[i] && (*cmd)[i] != '$')
// 		i++;
//         if ((*cmd)[i] == '\0')
//                 return (1);
// 	temp = copy_until_alnum_under(*cmd + i + 1);
// 	if (isin_2d_equal(env, temp) == 1)
// 	{
// 		temp2 = get_path_var(env, temp);
// 		replace_str(cmd, temp, temp2, i);
// 		return (0);
// 	}
// 	return (1);
// }

// int     main(int argc, char **argv, char **env)
// {
// 	char *main = ft_strdup(argv[1]);
// 	char *before = argv[2];
// 	char *after = argv[3];
// 	int	i = atoi(argv[4]);
// 	// replace_str(&main, argv[2], argv[3], &i);
//         expand(&main, env);
//         printf("|%s|\n$|%d|\n", main, i);
// 	free(main);
// }
