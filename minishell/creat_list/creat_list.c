/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lismarti <lismarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:25:55 by lismarti          #+#    #+#             */
/*   Updated: 2025/03/13 17:20:51 by lismarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		str = remove_all_quotes(content[j], 'a');
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
		if (str && strcmp(str, content[j++]) != 0)
			free(str);
	}
}
