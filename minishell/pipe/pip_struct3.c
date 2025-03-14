/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pip_struct3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smendez- <smendez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:26:23 by lismarti          #+#    #+#             */
/*   Updated: 2025/03/14 19:03:04 by smendez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	for_t2_and_t3(int stdo, t_list *pip, int t2)
{
	stdo = dup(STDOUT_FILENO);
	if (stdo == -1)
		return (stdo);
	if (t2 == 1)
		type1(pip);
	if (t2 == 3)
		type3(pip);
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
	else if (t1 == 7)
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
