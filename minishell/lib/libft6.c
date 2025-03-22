/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smendez- <smendez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:37:42 by lismarti          #+#    #+#             */
/*   Updated: 2025/03/22 18:51:43 by smendez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	isin_env(char **str, char *temp)
{
	int		j;
	int		count;
	int		size;

	j = 0;
	count = 0;
	if (!temp)
		return (1);
	while (str[j])
	{
		size = ft_strlen(temp);
		if (ft_strncmp(str[j], temp, size) == 0 && (str[j][size] == '=')
			|| str[j][size] == '\0')
			count++;
		j++;
	}
	if (count == 0)
		return (0);
	return (1);
}

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
	if (isin_env((*str2), temp) == 1)
		rmv_str_2d(str2, temp);
	nitems = str_len_2d(*str2);
	t = malloc((nitems + 2) * sizeof(char *));
	if (t == NULL)
		return (free(temp), 1);
	while (nitems > i)
	{
		t[i] = ft_strdup((*str2)[i]);
		if (!t[i++])
			return (-1);
	}
	t[i++] = ft_strdup(add);
	if (!t[i - 1])
		return (-1);
	return (t[i] = NULL, cleanexit(*str2), *str2 = t, free(temp), 0);
}

char	*copy_until(char *str, char c)
{
	int		i;
	char	*result;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	result = malloc(i + 1);
	if (!result)
		return (NULL);
	ft_strncpy(result, str, i);
	result[i] = '\0';
	return (result);
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
