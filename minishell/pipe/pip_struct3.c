/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pip_struct3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lismarti <lismarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:26:23 by lismarti          #+#    #+#             */
/*   Updated: 2025/03/05 17:37:02 by lismarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exe_build_single(t_list *pip, int t1, int t2)
{
	int	stdo;

	if (is_other(pip) == 1)
		;
	else if (t1 == 5)
		type5(pip);
	else if (t1 == 6)
		type6(pip);
	else if (t1 == 7)
		type7(pip);
	if (t2 == 1)
	{
		stdo = dup(STDOUT_FILENO);
		type1(pip);
	}
	else if (t2 == 2)
		type2(pip);
	else if (t2 == 3)
		type3(pip);
	ft_close_all(pip->data->fd);
	if (is_other(pip) == 1)
		exe_other(pip);
	if (t2 == 1)
		(dup2(stdo, STDOUT_FILENO), close(stdo));
}

void	type(t_list *pip, int t1, int t2)
{
	if (is_other(pip) == 1)
		;
	else if (t1 == 5)
		type5(pip);
	else if (t1 == 6)
		type6(pip);
	else if (t1 == 7)
		type7(pip);
	if (t2 == 1)
		type1(pip);
	else if (t2 == 2)
		type2(pip);
	else if (t2 == 3)
		type3(pip);
	ft_close_all(pip->data->fd);
}

void	exe_isolate(t_list *pip, int t1, int t2)
{
	char		**temp2;
	char		*no_a;
	char		*get_p;
	struct stat	st;

	type(pip, t1, t2);
	temp2 = ft_split_exe1(pip->cmd);
	no_a = no_args_cmd(temp2[0]);
	get_p = get_path_command(pip->data->path, no_a);
	if ((!get_p || !get_p[0]) && pip->data->path)
	{
		ft_printf_fd(2, "bash: %s: command not found\n", temp2[0]);
		(cleanexit(temp2), free_pip(pip), free(no_a), free(get_p), exit(127));
	}
	execve(get_p, temp2, *(pip->data->envp));
	if (stat(get_p, &st) == 0 && S_ISDIR(st.st_mode))
		ft_printf_fd(2, "bash: %s: Is a directory\n", no_a);
	else
		ft_printf_fd(2, "bashh: %s: %s\n", no_a, strerror(errno));
	if (errno == 2)
		errno = 127;
	else if (errno == 13)
		errno = 126;
	(cleanexit(temp2), free_pip(pip), free(no_a), free(get_p), exit(errno));
}

int	exe1(t_list *pip, int i)
{
	t_list	*head;

	head = pip;
	if (is_other(pip) == 1 && pip->data->n_cmd == 1 && pip->exe1 != 7)
		exe_build_single(pip, pip->exe1, pip->exe2);
	else
	{
		if (pip->exe1 == 7)
			signal(SIGINT, parent_her);
		pip->data->pid[0] = fork();
		if (pip->data->pid[0] == 0)
			(exe_isolate(pip, pip->exe1, pip->exe2));
	}
	while (i < pip->data->n_cmd)
	{
		pip = pip->next;
		pip->data->pid[i] = fork();
		if (pip->data->pid[i] == 0)
			(exe_isolate(pip, pip->exe1, pip->exe2));
		i++;
	}
	ft_close_all(pip->data->fd);
	i = wait_all(pip->data->pid, pip->data->n_cmd, pip);
	return (free_pip(head), i);
}
