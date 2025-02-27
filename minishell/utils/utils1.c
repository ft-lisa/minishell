#include "../minishell.h"

int	isin(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	**cleanexit(char **a)
{
	int	i;

	i = 0;
	while (a[i])
	{
		free(a[i]);
		i++;
	}
	free(a);
	return (NULL);
}

char	*cleanexit_int(int **a)
{
	int	i;

	i = 0;
	while (a[i])
	{
		free(a[i]);
		i++;
	}
	free(a);
	return (NULL);
}

int	lvl2_len(int **fd)
{
	int	i;

	i = 0;
	while (fd[i])
		i++;
	return (i);
}
char	*free_list(t_list *list)
{
	t_list	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		if (tmp->cmd)
		{
			printf("%p\n", tmp->cmd);
			free(tmp->cmd);
		}
			
		if (tmp->delim)
			cleanexit(tmp->delim);
		if (tmp->if_file1)
		{
			free(tmp->if_file1);
		}
			
		if (tmp->if_file2)
		{
			free(tmp->if_file2);
		}
			
		free(tmp);
	}
	return (NULL);
}
