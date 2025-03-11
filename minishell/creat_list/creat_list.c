#include "../minishell.h"

void	copy_new(char **new, int i, int j, char *str)
{
	while (i < j)
	{
		new[0][i] = str[i];
		i++;
	}
	new[0][i] = '\0';
	j = 0;
	while (str[i] != '\0')
	{
		new[1][j] = str[i];
		i++;
		j++;
	}
	new[1][j] = '\0';
}

char	**split_until(char *str, char c)
{
	int		i;
	int		size;
	char	**new;
	int		j;

	i = 0;
	j = 0;
	size = 0;
	new = malloc(3 * sizeof(char *));
	if (!new)
		return (NULL);
	while (str[size] != c)
		size++;
	new[0] = malloc((size + 1) * sizeof(char));
	new[1] = malloc((strlen(str) - size + 1) * sizeof(char));
	new[2] = NULL;
	if (!new[0] || !new[1])
		return (NULL);
	copy_new(new, i, size, str);
	return (new);
}

int	fill_seven_2(t_list *new, char **split_txt, int k, int i)
{
	char	**split;

	while (split_txt[i + 1])
	{
		if (operator(split_txt[i]) == 0)
		{
			new->delim[k++] = strdup(split_txt[i]);
			if (!new->delim[k - 1])
				return (-1);
		}
		i++;
	}
	split = ft_split(split_txt[i], ' ');
	if (split == NULL)
		return (-1);
	new->delim[k] = strdup(split[0]);
	if (!new->delim[k])
		return (-1);
	new->delim[k + 1] = NULL;
	new->cmd = ft_strdup(split[1]);
	if (!new->cmd)
		return (-1);
	cleanexit(split);
}
int	fill_seven_3(t_list *new, char **split_txt, int k, int i)
{
	new->cmd = ft_strdup(split_txt[0]);
	if (!new->cmd)
		return (-1);
	i++;
	while (split_txt[i])
	{
		if (operator(split_txt[i]) == 0)
		{
			new->delim[k++] = ft_strdup(split_txt[i]);
			if (!new->delim[k - 1])
				return (-1);
		}
		i++;
	}
	new->delim[k++] = NULL;
}

int	fill_seven(t_list *new, char *content)
{
	char	**split_txt;
	int		i;
	int		k;

	split_txt = ft_split_txt(content, 0, 0);
	if (split_txt == NULL)
		return (-1);
	i = 0;
	k = 0;
	new->delim = malloc((size_delim(split_txt, 0) + 1) * sizeof(char *));
	if (new->delim == NULL)
		return (-1);
	if (operator(split_txt[i]) == 7)
		if (fill_seven_2(new, split_txt, k, i) == -1)
			return (-1);
		else if (fill_seven_3(new, split_txt, k, i) == -1)
			return (-1);
	cleanexit(split_txt);
	return (1);
}

int	fill_one_three_2(char **split_txt, t_list *new)
{
	char	**split;

	split = ft_split(split_txt[1], ' ');
	if (!split)
		return (-1);
	new->if_file2 = ft_strdup(split[0]);
	if (!new->if_file2)
		return (-1);
	if (split[1])
	{
		new->cmd = ft_strdup(split[1]);
		if (!new->cmd)
			return (-1);
	}
	cleanexit(split);
}

int	fill_one_three(t_list *new, char *content)
{
	char	**split_txt;
	char	**split;

	split_txt = ft_split_txt(content, 0, 0);
	if (!split_txt)
		return (-1);
	if (operator(split_txt[0]) == 1 || operator(split_txt[0]) == 3)
    {
        if (fill_one_three_2(split_txt, new) == -1)
            return(-1);
    }
	else
	{
		new->cmd = ft_strdup(split_txt[0]);
		if (!new->cmd)
			return (-1);
		new->if_file2 = ft_strdup(split_txt[double_strlen(split_txt) - 1]);
		if (!new->if_file2)
			return (-1);
	}
	cleanexit(split_txt);
}
int	fill_six_two(char **split_txt, t_list *new)
{
	char	**split;

	split = ft_split(split_txt[1], ' ');
	if (!split)
		return (-1);
	new->if_file1 = ft_strdup(split[0]);
	if (!new->if_file1)
		return (-1);
	if (split[1])
	{
		new->cmd = ft_strdup(split[1]);
		if (!new->cmd)
			return (-1);
	}
	return (0);
	cleanexit(split);
}

int	fill_six(t_list *new, char *content)
{
	char	**split_txt;
	char	**split;

	split_txt = ft_split_txt(content, 0, 0);
	if (!split_txt)
		return (-1);
	if (operator(split_txt[0]) == 6)
    {
        if (fill_six_two(split_txt, new) == -1)
			return (-1);
    }
    else
    {
        new->cmd = ft_strdup(split_txt[0]);
        if (!new->cmd)
            return (-1);
        new->if_file1 = ft_strdup(split_txt[double_strlen(split_txt) - 1]);
        if (!new->if_file1)
            return (-1);
    }
	cleanexit(split_txt);
}



int	fill_com_list(t_list *list, char **content)
{
	char	**split;
	int		j;
	t_list	*new;

	new = list;
	j = 0;
	while (content[j])
	{
		if ((new->exe1 == 4 || new->exe1 == 5) && (new->exe2 == 2
				|| new->exe2 == 0))
		{
			new->cmd = ft_strdup(content[j]);
			if (new->cmd == NULL)
				return (-1);
		}
		if ((new->exe1 == 6 || new->exe1 == 7) && (new->exe2 == 1
				|| new->exe2 == 3))
		{
			split = split_until(content[j], '>');
			if (!split)
				return (-1);
			if (new->exe1 == 6)
				fill_six(new, split[0]);
			else
				fill_seven(new, split[0]);
			fill_one_three(new, split[1]);
			cleanexit(split);
		}
		else
		{
			if (new->exe1 == 6)
				fill_six(new, content[j]);
			if (new->exe1 == 7)
				fill_seven(new, content[j]);
			if (new->exe2 == 1 || new->exe2 == 3)
				fill_one_three(new, content[j]);
		}
		j++;
		new = new->next;
	}
}

int	fill_ope_list(t_list *list, char **content)
{
	int		j;
	t_list	*new;
	char	*str;

	j = 0;
	new = list;
	while (content[j])
	{
		new->index = j + 1;
		str = remove_all_quotes(content[j]);
		if (!str)
			return (-1);
		if (content[j + 1] != NULL)
		{
			new->exe2 = 2;
			new->next->exe1 = 5;
		}
		if (new->exe1 == -1 || (search_exe1(str) != 4 && new->exe1 == 5))
			new->exe1 = search_exe1(str);
		if (new->exe2 == -1 || (search_exe2(str) != 0 && new->exe2 == 2))
			new->exe2 = search_exe2(str);
		new = new->next;
		if (str && strcmp(str, content[j]) != 0)
			free(str);
		j++;
	}
}
