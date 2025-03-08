/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lismarti <lismarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:49:47 by lismarti          #+#    #+#             */
/*   Updated: 2025/03/08 10:05:11 by lismarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	isin2(const char *set, const char c)
{
	size_t	i;

	i = 0;
	while (set[i] != '\0' && set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	ft_strlentrim(const char *c, const char *set)
{
	size_t	i;
	size_t	k;

	i = 0;
	k = 0;
	while (c[k])
		k++;
	while (isin2(set, c[i]) == 1)
		i++;
	while (isin2(set, c[k - 1]) == 1)
		k--;
	if (k < i)
		return (0);
	return (k - i);
}

char	*ft_strtrim(char const *s1, const char *set)
{
	unsigned char	*t;
	size_t			i;
	size_t			j;
	size_t			sizetrim;

	i = 0;
	j = 0;
	sizetrim = ft_strlentrim(s1, set);
	t = malloc(sizetrim * sizeof(char) + 1);
	if (t == NULL)
		return (NULL);
	while (isin2(set, s1[i]) == 1)
		i++;
	while (j < sizetrim)
	{
		t[j] = s1[i + j];
		j++;
	}
	t[j] = '\0';
	return ((char *)t);
}
