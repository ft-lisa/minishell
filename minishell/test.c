#include "minishell.h"



// char	*copy_until_one(char *str, char *c)
// {
// 	int	i;
// 	int	size;
// 	char	*new;

// 	i = 0;
// 	size = 0;
// 	while (str[size])
// 		if (isin(c, str[size++]) == 1)
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

// int	replace_str(char **mainstr, char *before, char *after, int *index)
// {
// 	char	*new;
// 	int	i;
// 	int	len_a;
// 	int	len_b;

// 	i = 0;
// 	len_a = 0;
// 	if (after)
// 		len_a = ft_strlen(after);
// 	if (ft_strlen((*mainstr)) < *index)
// 		return (-1);
// 	if (before == NULL)
// 		return (-1);
// 	len_b = ft_strlen(before);
// 	new = malloc ((ft_strlen((*mainstr)) - len_b + len_a  + 1) * sizeof(char));
// 	while(i < *index)
// 	{
// 		new[i] = (*mainstr)[i];
// 		i++;
// 	}
// 	i = 0;
// 	while(after[i])
// 	{
// 		new[*index + i] = after[i];
// 		i++;
// 	}
// 	i = 0;
// 	while((*mainstr)[*index + len_b + i])
// 	{
// 		new[*index + len_a + i] = (*mainstr)[*index + len_b + i];
// 		i++;
// 	}
// 	new[*index + len_a + i] = '\0';
// 	free(*mainstr);
// 	*mainstr = new;
// 	*index = *index + len_a;
// 	return (0);
// }

// int     main(int argc, char **argv)
// {
// 	char *main = ft_strdup(argv[1]);
// 	char *before = argv[2];
// 	char *after = argv[3];
// 	int	i = atoi(argv[4]);
// 	replace_str(&main, argv[2], argv[3], &i);
//         printf("%s\n$|%d|\n", main, i);
// 	free(main);
// }
