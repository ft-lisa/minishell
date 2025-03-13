/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lismarti <lismarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:34:40 by lismarti          #+#    #+#             */
/*   Updated: 2025/03/13 15:34:41 by lismarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env1(t_list *pip)
{
	int		i;
	char	**str;

	str = ft_split(pip->cmd, ' ');
	if (!str)
		return (-1);
	if ((ft_strcmp(str[0], "env") == 0 && str[1] == NULL))
	{
		i = 0;
		while ((*(pip->data->envp))[i])
			printf("%s\n", (*(pip->data->envp))[i++]);
		ifexit(pip, str);
	}
	else
	{
		ft_printf_fd(2, "env: ʻ%s’: No such file or directory\n", str[1]);
		pip->data->new_exit = 127;
		ifexit(pip, str);
	}
}
