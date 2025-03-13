/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_operator3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lismarti <lismarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:32:58 by lismarti          #+#    #+#             */
/*   Updated: 2025/03/13 17:27:49 by lismarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	chck1op(char *str)
{
	char	*temp;
	int		i;

	if (!str || !str[0])
		return (0);
	temp = ft_strtrim(str, " ");
	if (!temp)
		return (1);
	i = 0;
	if (isin("<>", temp[0]) && !temp[1])
		(ft_printf_fd(2,
				"bash: syntax error near unexpected token `newline'\n"), i++);
	else if (isin("|", temp[0]) && !temp[1])
		(ft_printf_fd(2, "bash: syntax error near unexpected token `|'\n"),
			i++);
	else if (temp[1] && isin("|", temp[0]) && isin("|", temp[1]) && !temp[2])
		(ft_printf_fd(2, "bash: syntax error near unexpected token `||'\n"),
			i++);
	else if (isin("<", temp[0]) && temp[1] == '<' && !temp[2])
		(ft_printf_fd(2,
				"bash: syntax error near unexpected token `newline'\n"), i++);
	else if (isin(">", temp[0]) && temp[1] == '>' && !temp[2])
		(ft_printf_fd(2,
				"bash: syntax error near unexpected token `newline'\n"), i++);
	return (free(temp), i);
}

char	*remove_all_quotes(char *str, char del_q)
{
	char	*temp;
	char	*temp2;
	char	*join;

	del_q = pick_quote(str);
	temp = ft_strdup(str);
	if (!temp)
		return (NULL);
	while (count_c(temp, '\'') > 0 || count_c(temp, '\"') > 0)
	{
		temp2 = remove_first_quotes(temp);
		if (!temp2)
			return (free(temp), NULL);
		if (ft_strchr(temp2, '\'') == NULL && ft_strchr(temp2, '\"') == NULL)
			return (free(temp), temp2);
		free(temp);
		temp = ft_strdup(temp2);
		free(temp2);
		if (!temp)
			return (NULL);
		del_q = pick_quote(temp);
		if (count_c(temp, del_q) == 1)
			return (temp);
	}
	return (free(temp), str);
}
