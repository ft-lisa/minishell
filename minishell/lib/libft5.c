/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lismarti <lismarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:42:58 by lismarti          #+#    #+#             */
/*   Updated: 2025/03/06 14:43:01 by lismarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_only_one_quote(char *str)
{
	if (count_c(str, '\'') == 1 && count_c(str, '\"') == 0)
	{
		ft_printf_fd(2, "bash: syntax error: unclosed quotes\n");
		return (1);
	}
	else if (count_c(str, '\"') == 1 && count_c(str, '\'') == 0)
	{
		ft_printf_fd(2, "bash: syntax error: unclosed quotes\n");
		return (1);
	}
	else
		return (0);
}

long long	ft_atoll(const char *s)
{
	int			i;
	int			sign;
	long long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		result = result * 10 + (s[i] - '0');
		i++;
	}
	return (result * sign);
}
