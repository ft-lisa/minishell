/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smendez- <smendez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:21:43 by lismarti          #+#    #+#             */
/*   Updated: 2025/03/14 15:43:48 by smendez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exe_isolate(t_list *pip, int t1, int t2)
{
	char		**temp2;
	char		*no_a;
	char		*get_p;
	struct stat	st;

	type(pip, t1, t2);
	temp2 = ft_split_exe1(pip->cmd);
	if (!temp2)
		(free_pip(pip), exit (1));
	no_a = no_args_cmd(temp2[0]);
	if (!no_a)
		(free_pip(pip), exit(1));
	get_p = get_path_command(pip->data->path, no_a, 0, -1);
	if ((!get_p || !get_p[0] || !no_a[0]) && pip->data->path)
	{
		ft_printf_fd(2, "bash: %s: command not found\n", temp2[0]);
		(cleanexit(temp2), free_pip(pip), free(no_a), free(get_p), exit(127));
	}
	execve(get_p, temp2, *(pip->data->envp));
	// ft_printf_fd(2, "get_p |%s| no_a|%s| temp2|%s| \n", get_p, no_a, temp2[0]);
	if (get_p[0] && stat(get_p, &st) == 0 && S_ISDIR(st.st_mode))
		ft_printf_fd(2, "bash: %s: Is a directory\n", no_a);
	else
		ft_printf_fd(2, "bash: %s: %s\n", no_a, strerror(errno));
	ft_errno();
	(cleanexit(temp2), free_pip(pip), free(no_a), free(get_p), exit(errno));
}

void	exe2(t_list *pip)
{
	signal(SIGQUIT, parent_quit);
	if (pip->exe1 == 7)
	{
		signal(SIGINT, parent_her);
		signal(SIGQUIT, SIG_IGN);
	}
	pip->data->fd = ft_add_fd(pip->data->fd, 1);
	if (pipe(pip->data->fd[0]) == -1)
		perror("pipe1");
	pip->data->pid[0] = fork();
	if (pip->data->pid[0] == 0)
		(exe_isolate(pip, pip->exe1, pip->exe2));
}

int	exe1(t_list *pip, int i)
{
	t_list	*head;

	head = pip;
	
	if (is_other(pip) == 1 && pip->data->n_cmd == 1 && pip->exe1 != 7)
		exe_build_single(pip, pip->exe1, pip->exe2);
	else
		exe2(pip);
	while (i < pip->data->n_cmd)
	{
		pip->data->fd = ft_add_fd(pip->data->fd, i + 1);
		if (pipe(pip->data->fd[i]) == -1)
			perror("pipe1");
		pip = pip->next;
		if (pip->exe1 == 7)
			waitpid(pip->data->pid[pip->index - 2], NULL, 0);
		pip->data->pid[i] = fork();
		if (pip->data->pid[i] == -1)
			return (-1);
		if (pip->data->pid[i] == 0)
		{
			(exe_isolate(pip, pip->exe1, pip->exe2));
		}
		i++;
	}
	ft_close_all(pip->data->fd);
	i = wait_all(pip->data->pid, pip->data->n_cmd, pip);
	return (free_pip(head), i);
}
