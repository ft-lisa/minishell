/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lismarti <lismarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:33:46 by lismarti          #+#    #+#             */
/*   Updated: 2025/03/13 15:33:50 by lismarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	replace_str_2(int index, char **mainstr, char *new, char *after)
{
	int	i;

	i = 0;
	while (i < index)
	{
		new[i] = (*mainstr)[i];
		i++;
	}
	i = 0;
	while (after && after[i])
	{
		new[index + i] = after[i];
		i++;
	}
}

int	replace_str(char **mainstr, char *before, char *after, int index)
{
	char	*new;
	int		i;
	int		len_a;
	int		len_b;

	i = 0;
	len_a = 0;
	if (after)
		len_a = ft_strlen(after);
	if (before == NULL)
		return (-1);
	len_b = ft_strlen(before);
	new = malloc((ft_strlen((*mainstr)) - len_b + len_a + 1) * sizeof(char));
	if (!new)
		return (-1);
	replace_str_2(index, mainstr, new, after);
	while ((*mainstr)[index + len_b + 1])
	{
		new[index + len_a] = (*mainstr)[index + len_b + 1];
		index++;
	}
	new[index + len_a] = '\0';
	free(*mainstr);
	*mainstr = new;
	return (0);
}

int	isdollar_alone(char *str, int i)
{
	if (ft_isalnum(str[i + 1]) == 0 && str[i + 1] != '_' && str[i + 1] != '?')
		return (1);
	else
		return (0);
}
