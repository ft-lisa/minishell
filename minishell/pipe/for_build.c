/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lismarti <lismarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:41:55 by lismarti          #+#    #+#             */
/*   Updated: 2025/03/10 17:37:35 by lismarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_other(t_list *pip)
{
	int		ret;
	char	**str;

	ret = 0;
	if (isemptyor_spacetab(pip->cmd) == 1)
		return (0);
	str = ft_split_exe1(pip->cmd);
	if (!str)
		return (-1);
	if (ft_strcmp(str[0], "cd") == 0)
		ret = 1;
	else if (ft_strcmp(str[0], "pwd") == 0)
		ret = 1;
	else if (ft_strcmp(str[0], "env") == 0 && is_cmd_2d(pip) == 0)
		ret = 1;
	else if (ft_strcmp(str[0], "echo") == 0)
		ret = 1;
	else if (ft_strcmp(str[0], "exit") == 0)
		ret = 1;
	else if (ft_strcmp(str[0], "export") == 0)
		ret = 1;
	else if (ft_strcmp(str[0], "unset") == 0)
		ret = 1;
	cleanexit(str);
	return (ret);
}

void	exe_other(t_list *pip)
{
	char	*buf;
	int		i;
	char	**str;

	str = ft_split_exe1(pip->cmd);
	if (!str)
		(free_pip(pip), exit(1));
	if (ft_strcmp(str[0], "cd") == 0)
		(cleanexit(str), cd1(pip));
	else if (ft_strcmp(str[0], "pwd") == 0)
		(cleanexit(str), pwd1(pip));
	else if (ft_strcmp(str[0], "env") == 0)
		(cleanexit(str), env1(pip));
	else if (ft_strcmp(str[0], "echo") == 0)
		(echo1(pip), ifexit(pip, str));
	else if (ft_strcmp(str[0], "export") == 0)
		(export1(pip, str), ifexit(pip, str));
	else if (ft_strcmp(str[0], "unset") == 0)
		(unset1(pip, str), ifexit(pip, str));
	else if (ft_strcmp(str[0], "exit") == 0)
		if (check_exit(str, pip) == 1)
			(cleanexit(str), exit_minishell(pip));
}

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
		stdo = for_t2_and_t3(stdo, pip, t2);
	else if (t2 == 2)
		type2(pip);
	else if (t2 == 3)
		stdo = for_t2_and_t3(stdo, pip, t2);
	ft_close_all(pip->data->fd);
	if (is_other(pip) == 1)
		exe_other(pip);
	if (t2 == 1 || t2 == 3)
		if (dup2(stdo, STDOUT_FILENO) == -1 || close(stdo) == -1)
			return ;
}
