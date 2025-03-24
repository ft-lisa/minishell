/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smendez- <smendez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:37:42 by lismarti          #+#    #+#             */
/*   Updated: 2025/03/24 10:35:05 by smendez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*copy_until_diff_num(char *str)
{
	int		i;
	int		size;
	char	*new;

	i = 0;
	size = 0;
	while (str[size] && str[size] > 47 && str[size] < 58)
		size++;
	if (str[size] == '\0')
		return (ft_strdup(str));
	new = malloc((size + 1) * sizeof(char));
	if (!new)
		return (NULL);
	while (i < size)
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}
