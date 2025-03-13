/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lismarti <lismarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:36:22 by lismarti          #+#    #+#             */
/*   Updated: 2025/03/13 13:58:28 by lismarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	error_cd(char **str, t_list *pip)
{
	struct stat	path_stat;

	if (str[1][0] == '-' && str[1][1])
	{
		ft_printf_fd(2, "bash: cd: %c%c: invalid option\n", str[1][0],
			str[1][1]);
		pip->data->new_exit = 2;
	}
	if (stat(str[1], &path_stat) == -1)
	{
		ft_printf_fd(2, "bash: cd: %s: No such file or directory\n", str[1]);
		pip->data->new_exit = 1;
	}
	else
	{
		if (!S_ISDIR(path_stat.st_mode))
			ft_printf_fd(2, "bash: cd: Not a directory: %s\n", str[1]);
		else
			ft_printf_fd(2, "bash: cd: Permission denied: %s\n", str[1]);
		pip->data->new_exit = 1;
	}
}

char* cd_pwd_2(char* temp, char* path, t_list* pip)
{
        temp = ft_strjoin("PWD=", path);
        if (!temp)
                (exit_minishell(pip), exit(1));
        add_last_2d(pip->data->envp, temp);
        free(temp);
        return(temp);
}

int	cd_pwd(t_list *pip, char *buf)
{
	int		ret;
	char	*temp;
	char	*path;

	ret = chdir(buf);
	if (ret != -1)
	{
		path = get_path_var(*(pip->data->envp), "PWD");
		if (path)
		{
			temp = ft_strjoin("OLDPWD=", path);
			if (!temp)
                                (free_pip(pip), exit(1));
			add_last_2d(pip->data->envp, temp);
			free(temp);
		}
		path = pwd2(pip);
		if (path)
		{
			temp = cd_pwd_2(temp, path, pip);
		}
		free(path);
	}
	return (ret);
}

void cd2(char* buf, t_list* pip, int ret)
{
        buf = get_path_var(*(pip->data->envp), "HOME");
        if (buf)
                ret = cd_pwd(pip, buf);
        if (buf == NULL || ret == -1)
        {
                ft_printf_fd(2, "bash: cd: HOME not set\n");
                pip->data->new_exit = 1;
        }
}

int	cd1(t_list *pip)
{
	char	**str;
	char	*buf;
	int		ret;

	str = ft_split(pip->cmd, ' ');
	if (!str)
		exit_minishell(pip);
	if (str_len_2d(str) > 2)
	{
		ft_printf_fd(2, "bash: cd: too many arguments\n");
		pip->data->new_exit = 1;
	}
	else if (ft_strcmp(str[0], "cd") == 0 && !str[1])
	{
		cd2(buf, pip, ret);
	}
	else if (ft_strcmp(str[0], "cd") == 0 && str[1])
	{
		ret = cd_pwd(pip, str[1]);
		if (ret == -1)
		{
			error_cd(str, pip);
		}
	}
	ifexit(pip, str);
}
