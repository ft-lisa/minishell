/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pip_struct2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lismarti <lismarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:41:18 by lismarti          #+#    #+#             */
/*   Updated: 2025/03/10 14:22:17 by lismarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_close_all(int **fd)
{
	int	i;
	int	j;

	i = 0;
	if (!fd || !fd[0])
		return ;
	while (fd[i])
	{
		j = 0;
		while (j < 2)
		{
			if (fd[i][j] != -1)
				if (close(fd[i][j]) == -1)
					return ;
			j++;
		}
		i++;
	}
}

int	ft_strrchr(const char *string, int searchedChar)
{
	int	i;
	int	check;
	int	result;

	i = 0;
	check = 0;
	while (string[i] != '\0')
	{
		if (string[i] == (unsigned char)searchedChar)
		{
			result = i;
			check++;
		}
		i++;
	}
	if (string[i] == (unsigned char)searchedChar)
	{
		result = i;
		check++;
	}
	if (check != 0)
		return (result);
	return (0);
}

char	*recup_path(char *src)
{
	unsigned int	i;
	unsigned int	n;
	int				size;
	char			*dst;

	size = ft_strrchr(src, '/');
	i = 0;
	n = size;
	if (size == 0)
		return (NULL);
	dst = malloc(size + 2);
	if (!dst)
		return(NULL);
	while (i < n && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

void	for_fork(int i, t_list *pip)
{
	if (pip->data->pid[i] == -1)
		return ;
	if (pip->data->pid[i] == 0)
		(exe_isolate(pip, pip->exe1, pip->exe2));
}
