/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lismarti <lismarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:38:06 by lismarti          #+#    #+#             */
/*   Updated: 2025/03/13 16:54:45 by lismarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*pwd2(t_list *pip)
{
	char	*buf;
	char	*err;
	char	**str;

	buf = malloc(4097 * sizeof(char));
	if (!buf)
		exit_minishell(pip);
	err = getcwd(buf, 4096);
	if (!err)
	{
		ft_printf_fd(2, "chdir: %s", ERROR_DIREC);
		free(buf);
		return (NULL);
	}
	return (buf);
}

void	pwd3(t_list *pip, char *buf, char *err, char **str)
{
	buf = malloc(4097 * sizeof(char));
	if (!buf)
		exit_minishell(pip);
	err = getcwd(buf, 4096);
	if (err)
		printf("%s\n", buf);
	else
	{
		ft_printf_fd(2, "pwd: %s", ERROR_DIREC);
		pip->data->new_exit = 1;
	}
	free(buf);
	ifexit(pip, str);
}

int	pwd1(t_list *pip)
{
	char	*buf;
	char	*err;
	char	**str;

	str = ft_split(pip->cmd, ' ');
	if (!str)
		return (-1);
	if (str[1])
	{
		if (str[1][0] == '-' && str[1][1])
		{
			ft_printf_fd(2, "bash: pwd: %c%c: invalid option\n", str[1][0],
				str[1][1]);
			pip->data->new_exit = 2;
			ifexit(pip, str);
			return (2);
		}
	}
	pwd3(pip, buf, err, str);
	return (0);
}
