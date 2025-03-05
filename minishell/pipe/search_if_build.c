/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_if_build.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lismarti <lismarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:41:55 by lismarti          #+#    #+#             */
/*   Updated: 2025/03/05 17:42:02 by lismarti         ###   ########.fr       */
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
	{
		if (check_exit(str, pip) == 1)
		{
			(cleanexit(str), exit_minishell(pip));
		}
	}
}
