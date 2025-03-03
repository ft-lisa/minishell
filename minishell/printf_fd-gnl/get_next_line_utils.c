/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lismarti <lismarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 17:38:45 by smendez-          #+#    #+#             */
/*   Updated: 2025/03/03 19:37:23 by lismarti         ###   ########.fr       */
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

void	ft_until_limiter(char *argv, int verbose, int* write_fd)
{
	char	*line;
	char	*delimiter;
	int		bomb;
	static int num = 1;

	bomb = 0;
	delimiter = argv;
	while (bomb == 0)
	{
		signal(SIGINT, her);
		line = readline("> ");
		if(sig_g == 2)
		{
			close(write_fd[0]);
			close(write_fd[1]);
			free(line);
			return ;
		}
		if (line == NULL)
		{
			printf("bash: warning: here-document at line %d delimited by end-of-file (wanted `%s') sad\n", num, argv);
			return ;
		}
		if (ft_strcmp(delimiter, line) == 0)
		{
			free(line);
			bomb = 1;
			break ;
		}
		if (verbose == 1)
		{
			write(write_fd[1], line, ft_strlen(line));
			write(write_fd[1], "\n", 1);
		}
		free(line);
	}
	if (verbose == 1)
		num++;
}
