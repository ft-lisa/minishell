/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lismarti <lismarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:37:42 by lismarti          #+#    #+#             */
/*   Updated: 2025/03/10 14:46:00 by lismarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	add_last_2d(char ***str2, char *add)
{
	char	**t;
	int		i;
	int		nitems;
	char	*temp;

	i = 0;
	temp = copy_until(add, '=');
	if (!temp)
		return (1);
	if (isin_2d_equal((*str2), temp) == 1)
		rmv_str_2d(str2, temp);
	nitems = str_len_2d(*str2);
	t = malloc((nitems + 2) * sizeof(char *));
	if (t == NULL)
		return (free(temp), 1);
	while (nitems > i)
	{
		t[i] = ft_strdup((*str2)[i]);
		if (!t[i])
			return(-1);
		i++;
	}
	t[i++] = ft_strdup(add);
	if (!t[i - 1])
		return(-1);
	t[i] = NULL;
	cleanexit(*str2);
	*str2 = t;
	return (free(temp), 0);
}

char	*copy_until(char *str, char c)
{
	int		i;
	int		size;
	char	*new;

	i = 0;
	size = 0;
	while (str[size])
		if (str[size++] == c)
			break ;
	if (str[size] == '\0')
		return (ft_strdup(str));
	size = (size > 0) * (size - 1);
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

char	*copy_until_one(char *str, char *c)
{
	int		i;
	int		size;
	char	*new;

	i = 0;
	size = 0;
	while (str[size])
		if (isin(c, str[size++]) == 1)
			break ;
	if (str[size] == '\0')
		return (ft_strdup(str));
	size--;
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

char	*copy_until_alnum_under(char *str)
{
	int		i;
	int		size;
	char	*new;

	i = 0;
	size = 0;
	while (str[size])
	{
		size++;
		if (ft_isalnum(str[size]) == 0 || str[size] == '_')
			break ;
	}
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
