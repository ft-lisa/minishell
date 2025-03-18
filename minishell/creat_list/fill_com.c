/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_com.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smendez- <smendez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:33:11 by lismarti          #+#    #+#             */
/*   Updated: 2025/03/18 15:29:29 by smendez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fill_com_list_3(char **content, t_list *new, int j)
{
	if (new->exe1 == 6)
		fill_six(new, content[j]);
	if (new->exe1 == 7)
		fill_seven(new, content[j]);
	if (new->exe2 == 1 || new->exe2 == 3)
		fill_one_three(new, content[j]);
	return (0);
}

int	fill_com_list_2(char **content, t_list *new, int j)
{
	char	**split;

	if ((new->exe1 == 6 || new->exe1 == 7) && (new->exe2 == 1
			|| new->exe2 == 3))
	{
		split = split_until(content[j], '>');
		if (!split)
			return (-1);
		if (new->exe1 == 6)
		{
			if (fill_six(new, split[0]) == -1)
				return (-1);
		}
		else
		{
			if (fill_seven(new, split[0]) == -1)
				return (-1);
		}
		if (fill_one_three(new, split[1]) == -1)
			return (-1);
		cleanexit(split);
	}
	else
		return (fill_com_list_3(content, new, j));
	return (0);
}

int	fill_com_list(t_list *list, char **content)
{
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
		if (fill_com_list_2(content, new, j) == -1)
			return (-1);
		j++;
		new = new->next;
	}
	return (0);
}
