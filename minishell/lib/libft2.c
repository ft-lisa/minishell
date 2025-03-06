/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lismarti <lismarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:36:32 by lismarti          #+#    #+#             */
/*   Updated: 2025/03/06 14:36:54 by lismarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	str_len_2d(char **str)
{
	int	j;

	j = 0;
	while (str[j])
	{
		j++;
	}
	return (j);
}

char	**strdup_2d(char **s)
{
	char	**t;
	int		i;
	int		j;
	int		nitems;

	i = 0;
	j = 0;
	nitems = str_len_2d(s);
	t = malloc((nitems + 1) * sizeof(char *));
	if (t == NULL)
		return (NULL);
	while (nitems > i)
	{
		t[i] = ft_strdup(s[i]);
		i++;
	}
	t[i] = NULL;
	return (t);
}

int	isin_2d_equal(char **str, char *check)
{
	int		j;
	int		count;
	char	*temp;

	j = 0;
	count = 0;
	temp = ft_strjoin(check, "=");
	if (!temp)
		return (1);
	while (str[j])
	{
		if (ft_strncmp(str[j++], temp, strlen(temp)) == 0)
			count++;
	}
	if (count == 0)
		return (free(temp), 0);
	free(temp);
	return (1);
}

int	isin_2d_index(char **str, char *check)
{
	int		j;
	int		count;
	char	*temp;

	j = 0;
	count = 0;
	temp = ft_strjoin(check, "=");
	if (!temp)
		return (1);
	while (str[j])
	{
		if (ft_strncmp(str[j], temp, strlen(temp)) == 0)
			return (free(temp), j);
		j++;
	}
	return (free(temp), -1);
}

int	isin_2d_delim(char **str, char *check, char delim)
{
	int		j;
	int		count;
	char	*temp;

	j = 0;
	count = 0;
	while (str[j])
	{
		temp = copy_until(str[j], delim);
		if (!temp)
			return (1);
		if (ft_strcmp(temp, check) == 0)
			count++;
		free(temp);
		j++;
	}
	if (count == 0)
		return (0);
	return (1);
}
