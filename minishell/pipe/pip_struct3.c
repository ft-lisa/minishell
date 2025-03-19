/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pip_struct3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smendez- <smendez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:26:23 by lismarti          #+#    #+#             */
/*   Updated: 2025/03/19 10:51:15 by smendez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	for_t1_and_t3(int stdo, t_list *pip, int t2)
{
	int	er_file;

	er_file = 0;
	if (ft_strncmp(pip->cmd, "exit", 4) != 0)
	{
		stdo = dup(STDOUT_FILENO);
		if (stdo == -1)
			(free_pip(pip), exit(EXIT_FAILURE));
	}
	if (stdo == -1)
		return (stdo);
	if (t2 == 1)
		er_file = type1(pip);
	if (t2 == 3)
		er_file = type3(pip);
	if (er_file == -2)
		close(stdo);
	return (stdo);
}

void	type(t_list *pip, int t1, int t2)
{
	if (is_other(pip) == 1)
		;
	else if (t1 == 5)
		type5(pip);
	else if (t1 == 6)
		type6(pip);
	if (t1 == 7)
		type7(pip);
	if (t2 == 1)
		type1(pip);
	else if (t2 == 2)
		type2(pip);
	else if (t2 == 3)
		type3(pip);
	ft_close_all(pip->data->fd);
	if (is_other(pip) == 1)
		exe_other(pip);
}

void	ft_errno(void)
{
	if (errno == 2)
		errno = 127;
	else if (errno == 13)
		errno = 126;
}
