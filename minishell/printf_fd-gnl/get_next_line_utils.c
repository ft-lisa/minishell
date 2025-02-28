/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smendez- <smendez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 17:38:45 by smendez-          #+#    #+#             */
/*   Updated: 2025/02/28 14:02:09 by smendez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_calloc2(size_t nitems, size_t size)
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

int	isin1(const char *set, const char c, int buffersize)
{
	int	i;

	i = 0;
	if (!set)
		return (0);
	while (buffersize > i)
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return(-1);
	while (s1[i] != '\0' && s1[i] == s2[i])
		i++;
	j = s1[i] - s2[i];
	return (j);
}

void	ft_putstr_fd1(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

void	ft_until_limiter(char *argv, int verbose)
{
	char	*line;
	char	*delimiter;
	int		bomb;

	bomb = 0;
	delimiter = ft_strjoin(argv, "\n");
	while (bomb == 0)
	{
		ft_putstr_fd1("> ", 0);
		line = get_next_line(0);
		if (ft_strcmp(delimiter, line) == 0)
		{
			free(line);
			bomb = 1;
			line = get_next_line(-14);
			free(delimiter);
			break ;
		}
		if (verbose == 1)
			ft_putstr_fd1(line, 1);
		free(line);
	}
}
