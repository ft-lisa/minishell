/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_7_1_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lismarti <lismarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:33:19 by lismarti          #+#    #+#             */
/*   Updated: 2025/03/13 17:40:31 by lismarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
        cleanexit(split);
	if (!new->cmd)
		return (-1);	
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
	{
		if (fill_seven_2(new, split_txt, k, i) == -1)
			return (cleanexit(split_txt), -1);
	}
	else if (fill_seven_3(new, split_txt, k, i) == -1)
		return (cleanexit(split_txt), -1);
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
			return (-1);
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
