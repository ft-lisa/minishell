/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lismarti <lismarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:09:29 by lismarti          #+#    #+#             */
/*   Updated: 2025/03/05 15:09:30 by lismarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isalldigit(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	check_long_long(char *str)
{
	unsigned long long	num;
	int					i;
	int					neg;

	num = 0;
	i = 0;
	neg = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			neg = 1;
		i++;
	}
	while (str[i])
	{
		num = num * 10 + (str[i] - '0');
		if ((!neg && num > 9223372036854775807ULL) || (neg
				&& num > 9223372036854775808ULL))
			return (0);
		i++;
	}
	return (1);
}

void	exit_minishell_error(t_list *pip)
{
	rl_clear_history();
	free_pip(pip);
	exit(2);
}

int	check_exit(char **str, t_list *pip)
{
	if (!str[1])
		return (1);
	if (!ft_isalldigit(str[1]))
	{
		ft_printf_fd(2, "bash: exit: %s: numeric argument required\n", str[1]);
		exit_minishell_error(pip);
	}
	if (!check_long_long(str[1]))
	{
		ft_printf_fd(2, "bash: exit: %s: numeric argument required\n", str[1]);
	}
	if (str[2])
	{
		pip->data->new_exit = 1;
		return (ft_printf_fd(2, "bash: exit: too many arguments\n"), 0);
	}
	return (1);
}
