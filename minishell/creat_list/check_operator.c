/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lismarti <lismarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 10:53:33 by lismarti          #+#    #+#             */
/*   Updated: 2025/03/13 15:25:40 by lismarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	isconsecutive_ops1_index(char *str, char *op)
{
	char	*temp;
	int		i;

	temp = ft_strstr(str, op);
	i = ft_strlen(op);
	if (!temp || temp[0] == '\0')
		return (ft_strlen(str));
	if (temp[1] && temp[0] == temp[1] && i == 1 && (temp[0] == '<'
			|| temp[0] == '>'))
		temp = temp + 1;
	while (temp[i] && temp[i] == ' ')
		i++;
	if (temp[i] && temp[i + 1] && isin("|<>", temp[i]) == 1 && isin("|<>",
			temp[i + 1]) == 0)
		return (ft_strlen(str) - ft_strlen(temp));
	else if (temp[i] && !temp[i + 1] && isin("|<>", temp[i]) == 1)
		return (ft_strlen(str) - ft_strlen(temp));
	else if (temp[i] && temp[i + 1] && isin("|<>", temp[i]) == 1 && isin("|<>",
			temp[i + 1]) == 1)
		return (ft_strlen(str) - ft_strlen(temp));
	return (ft_strlen(str));
}

int	isconsecutive_opsloop_index(char *str, char *op)
{
	int		i;
	char	*temp;
	int		check;
	int		len;

	i = 0;
	len = ft_strlen(str);
	temp = ft_strstr(str, op);
	if (!temp || temp[0] == '\0')
		return (ft_strlen(str));
	check = isconsecutive_ops1_index(str, op);
	while (temp && temp[0] && check == len)
	{
		if (!temp[1])
			break ;
		temp = ft_strstr(temp + 2, op);
		if (temp)
			check = isconsecutive_ops1_index(temp, op);
	}
	return (check);
}

int	chck2op_type(char *str)
{
	int	i[5];
	int	j;
	int	min;

	j = 0;
	if (!i)
		return (-1);
	min = 0;
	i[0] = isconsecutive_opsloop_index(str, "<<");
	i[1] = isconsecutive_opsloop_index(str, ">>");
	i[2] = isconsecutive_opsloop_index(str, "<");
	i[3] = isconsecutive_opsloop_index(str, ">");
	i[4] = isconsecutive_opsloop_index(str, "|");
	while (j < 5)
	{
		if (i[j] < i[min])
			min = j;
		j++;
	}
	return (min);
}

int	isconsecutive_ops1(char *str, char *op, int j)
{
	char	*temp;
	int		i;

	temp = ft_strstr(str, op);
	i = ft_strlen(op);
	if (!temp || temp[0] == '\0')
		return (0);
	if (temp[1] && temp[0] == temp[1] && i == 1 && (temp[0] == '<'
			|| temp[0] == '>'))
		temp = temp + 1;
	while (temp[i] && temp[i] == ' ')
		i++;
	if (temp[i] && temp[i + 1] && *op == '|' && isin("<>", temp[i + 1]) == 1)
		(ft_printf_fd(2, ERROR_MESS "'%c'\n", *op), j++);
	else if (temp[i] && temp[i + 1] && isin("|<>", temp[i]) == 1 && isin("|<>",
			temp[i + 1]) == 0)
		(ft_printf_fd(2, ERROR_MESS "`%c'\n", temp[i]), j++);
	else if (temp[i] && !temp[i + 1] && isin("|<>", temp[i]) == 1)
		(ft_printf_fd(2, ERROR_MESS "`%c'\n", temp[i]), j++);
	else if (temp[i] && temp[i + 1] && isin("|<>", temp[i]) == 1 && isin("|<>",
			temp[i + 1]) == 1)
		(ft_printf_fd(2, ERROR_MESS "`%c%c'\n", temp[i], temp[i + 1]), j++);
	return (j);
}

int	isconsecutive_opsloop(char *str, char *op)
{
	int		i;
	char	*temp;
	int		check;

	i = 0;
	temp = ft_strstr(str, op);
	if (!temp || temp[0] == '\0')
		return (0);
	check = isconsecutive_ops1(str, op, 0);
	while (temp && temp[0] && check == 0)
	{
		if (!(temp[1]) || !temp)
			return (check);
		temp = ft_strstr(temp + 2, op);
		if (temp)
			check = isconsecutive_ops1(temp, op, 0);
	}
	return (check);
}
