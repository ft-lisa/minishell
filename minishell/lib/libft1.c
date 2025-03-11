/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lismarti <lismarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:36:18 by lismarti          #+#    #+#             */
/*   Updated: 2025/03/11 13:01:24 by lismarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin(char const *s1, const char *s2)
{
	char	*t;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	t = malloc((ft_strlen(s1) + ft_strlen(s2)) * sizeof(char) + 1);
	if (t == NULL)
		return (NULL);
	while (s1[i])
	{
		t[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		t[i + j] = s2[j];
		j++;
	}
	t[i + j] = '\0';
	return (t);
}

void	*ft_calloc(size_t nitems, size_t size)
{
	unsigned char	*t;
	size_t			i;
	size_t			k;

	i = 0;
	if (size != 0 && (nitems * size) / size != nitems)
		return (NULL);
	k = nitems * size;
	t = malloc(k);
	if (!t)
		return (NULL);
	while (nitems * size > i)
	{
		t[i] = 0;
		i++;
	}
	return (t);
}

char	*ft_strdup(const char *s)
{
	char	*t;
	size_t	i;
	size_t	nitems;

	i = 0;
	if (s == NULL)
		return(NULL);
	nitems = ft_strlen(s);
	t = malloc(nitems * sizeof(char) + 1);
	if (t == NULL)
		return (NULL);
	while (nitems > i)
	{
		t[i] = s[i];
		i++;
	}
	t[i] = '\0';
	return (t);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	j;
	unsigned int	i;

	if (n == 0)
		return (0);
	i = 0;
	j = 0;
	while (s1[i] != '\0' && s1[i] == s2[i] && i < n - 1)
		i++;
	j = (unsigned char)s1[i] - (unsigned char)s2[i];
	return (j);
}
