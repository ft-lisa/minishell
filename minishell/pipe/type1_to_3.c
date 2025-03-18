/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type1_to_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smendez- <smendez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:21:09 by lismarti          #+#    #+#             */
/*   Updated: 2025/03/18 17:15:47 by smendez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* void	type1(t_list *pip)
{
	int		fd_out;
	char	*path;

	if (isin(pip->if_file2, '/') == 1)
	{
		path = recup_path(pip->if_file2);
		if (access(path, F_OK) == -1)
		{
			ft_printf_fd(2, ERROR_FIND, pip->if_file2);
			if (is_other(pip) == 1 && pip->data->n_cmd == 1)
			{
				pip->data->new_exit = 1;
				return ;
			}
			(free(path), free_pip(pip), exit(EXIT_FAILURE));
		}
		free(path);
	}
	if (access(pip->if_file2, F_OK) == 0 && access(pip->if_file2, W_OK) == -1)
	{
		ft_printf_fd(2, "bash: permission denied: %s\n", pip->if_file2);
		if (is_other(pip) == 1 && pip->data->n_cmd == 1)
		{
			pip->data->new_exit = 1;
			return ;
		}
		(free_pip(pip), exit(EXIT_FAILURE));
	}
	fd_out = open(pip->if_file2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		(free_pip(pip), exit(1));
	close(fd_out);
} */

int	type1(t_list *pip)
{
	int		fd_out;
	char	*path;

	if (isin(pip->if_file2, '/') == 1)
	{
		path = recup_path(pip->if_file2);
		if (access(path, F_OK) == -1)
		{
			ft_printf_fd(2, ERROR_FIND, pip->if_file2);
			if (is_other(pip) == 1 && pip->data->n_cmd == 1)
				return (pip->data->new_exit = 1, free(path), -2);
			(free(path), free_pip(pip), exit(EXIT_FAILURE));
		}
		free(path);
	}
	if (access(pip->if_file2, F_OK) == 0 && access(pip->if_file2, W_OK) == -1)
	{
		ft_printf_fd(2, "bash: permission denied: %s\n", pip->if_file2);
		if (is_other(pip) == 1 && pip->data->n_cmd == 1)
			return (pip->data->new_exit = 1, -2);
		(free_pip(pip), exit(EXIT_FAILURE));
	}
	fd_out = open(pip->if_file2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (dup2(fd_out, STDOUT_FILENO) == -1 || close(fd_out) == -1)
		(free_pip(pip), exit(1));
}

void	type1bis(t_list *pip)
{
	int	fd_out;

	if (access(pip->if_file2, F_OK) == 0 && access(pip->if_file2, W_OK) == -1)
	{
		ft_printf_fd(2, "bash: permission denied: %s\n", pip->if_file2);
		(free_pip(pip), exit(EXIT_FAILURE));
	}
	fd_out = open(pip->if_file2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		(free_pip(pip), exit(1));
	close(fd_out);
}

void	type2(t_list *pip)
{
	if (dup2(pip->data->fd[pip->index - 1][1], STDOUT_FILENO) == -1)
		(perror("dup2 1"), exit(EXIT_FAILURE));
}

int	type3(t_list *pip)
{
	int		fd_out;
	char	*path;

	if (isin(pip->if_file2, '/') == 1)
	{
		path = recup_path(pip->if_file2);
		if (access(path, F_OK) == -1)
		{
			ft_printf_fd(2, ERROR_FIND, pip->if_file2);
			if (is_other(pip) == 1 && pip->data->n_cmd == 1)
				return (pip->data->new_exit = 1, free(path), -2);
			(free(path), free_pip(pip), exit(EXIT_FAILURE));
		}
		free(path);
	}
	if (access(pip->if_file2, F_OK) == 0 && access(pip->if_file2, W_OK) == -1)
	{
		ft_printf_fd(2, "bash: permission denied: %s\n", pip->if_file2);
		if (is_other(pip) == 1 && pip->data->n_cmd == 1)
			return (pip->data->new_exit = 1, -2);
		(free_pip(pip), exit(EXIT_FAILURE));
	}
	fd_out = open(pip->if_file2, O_APPEND | O_WRONLY | O_CREAT, 0644);
	if (dup2(fd_out, STDOUT_FILENO) == -1 || close(fd_out) == -1)
		(free_pip(pip), exit(1));
}

/* void	type3(t_list *pip)
{
	int	fd_out;

	if (access(pip->if_file2, F_OK) == 0 && access(pip->if_file2, W_OK) == -1)
	{
		ft_printf_fd(2, "bash: permission denied: %s\n", pip->if_file2);
		(free_pip(pip), exit(EXIT_FAILURE));
	}
	fd_out = open(pip->if_file2, O_APPEND | O_WRONLY | O_CREAT, 0644);
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		(free_pip(pip), exit(1));
	close(fd_out);
} */
