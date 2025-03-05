/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pip_struct4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lismarti <lismarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:39:09 by lismarti          #+#    #+#             */
/*   Updated: 2025/03/05 17:40:52 by lismarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_cmd(t_list *pip)
{
	char	*no_a;
	char	*get_p;
	int		r;

	r = 1;
	if (!pip)
		return (0);
	no_a = no_args_cmd(pip->cmd);
	get_p = get_path_command(pip->data->path, no_a);
	if (get_p[0] == '\0')
		r = 0;
	free(no_a);
	free(get_p);
	return (r);
}

int	is_cmd_2d(t_list *pip)
{
	char	**temp2;
	char	*no_a;
	char	*get_p;
	int		r;

	r = 1;
	if (!pip)
		return (0);
	temp2 = ft_split_exe1(pip->cmd);
	no_a = no_args_cmd(temp2[1]);
	get_p = get_path_command(pip->data->path, no_a);
	if (get_p[0] == '\0')
		r = 0;
	free(no_a);
	free(get_p);
	cleanexit(temp2);
	return (r);
}

char	*get_path_var(char *envp[], char *p1)
{
	int	i;
	int	j;
	int	len_p1;

	i = 0;
	len_p1 = ft_strlen(p1);
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] && envp[i][j] == p1[j])
			j++;
		if (j == len_p1 && envp[i][j] == '=')
		{
			return (envp[i] + j + 1);
		}
		i++;
	}
	return (NULL);
}

void	ifexit(t_list *pip, char **str)
{
	int	exit1;

	cleanexit(str);
	if (pip->data->n_cmd > 1)
	{
		exit1 = pip->data->new_exit;
		free_pip(pip);
		exit(exit1);
	}
}

void	ft_until_limiter(char *delimiter, int verbose, int *write_fd)
{
	char	*line;

	signal(SIGINT, her);
	while (1)
	{
		line = readline("> ");
		if (g_sig == 2)
			return (close(write_fd[0]), close(write_fd[1]), free(line));
		if (line == NULL)
		{
			ft_printf_fd(2, "bash: warning: here-document delimited ");
			ft_printf_fd(2, "by end-of-file wanted `%s') sad\n", delimiter);
			return ;
		}
		if (ft_strcmp(delimiter, line) == 0)
			return (free(line));
		if (verbose == 1)
		{
			write(write_fd[1], line, ft_strlen(line));
			write(write_fd[1], "\n", 1);
		}
		free(line);
	}
}
