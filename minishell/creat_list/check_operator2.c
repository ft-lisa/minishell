/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_operator2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lismarti <lismarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:32:35 by lismarti          #+#    #+#             */
/*   Updated: 2025/03/13 17:27:37 by lismarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	chck2op(char *str)
{
	char	*temp;
	char	**op;
	int		i;

	if (!str || !str[0])
		return (0);
	temp = ft_strtrim(str, " ");
	if (!temp)
		return (1);
	i = chck2op_type(str);
	op = ft_split("<< >> < > |", ' ');
	if (!op)
		return (-1);
	if (isconsecutive_opsloop(str, op[i]) == 1)
		return (free(temp), cleanexit(op), 1);
	else if (isin("<>|", temp[ft_strlen(temp) - 1]) == 1)
	{
		(ft_printf_fd(2,
				"bash: syntax error near unexpected token `newline'\n"));
		return (free(temp), cleanexit(op), 1);
	}
	return (free(temp), cleanexit(op), 0);
}

char	pick_quote(char *str)
{
	char	del_q;
	char	*p_single;
	char	*p_double;

	p_single = ft_strchr(str, '\'');
	p_double = ft_strchr(str, '\"');
	if (p_single && p_double)
	{
		if (p_single < p_double)
			del_q = '\'';
		else
			del_q = '\"';
	}
	else if (p_single)
		del_q = '\'';
	else
		del_q = '\"';
	return (del_q);
}

char	*join_parts(char *temp, char *temp2, int mode)
{
	char	*join;

	if (mode == 1)
	{
		temp2 = ft_strjoin("Z", temp2);
		if (!temp2)
			return (NULL);
		join = ft_strjoin(temp, temp2);
		free(temp2);
	}
	else if (!temp || !temp[0])
		join = ft_strdup(temp2);
	else
	{
		temp2 = ft_strjoin(temp, "Z");
		return (free(temp), temp2);
	}
	return (free(temp), join);
}

char	*remove_first_quotes(char *str)
{
	char	*temp;
	char	*temp2;
	char	del_q;

	if (!ft_strchr(str, '\'') && !ft_strchr(str, '"'))
		return (str);
	del_q = pick_quote(str);
	temp = copy_until(str, del_q);
	if (!temp)
		return (NULL);
	temp2 = ft_strchr(str, del_q) + 1;
	temp2 = ft_strchr(temp2, del_q) + 1;
	if (temp && temp2 && temp[0] && temp2[0])
		return (join_parts(temp, temp2, 1));
	return (join_parts(temp, temp2, 0));
}

int	check_operator(char *str1)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = remove_all_quotes(str1, 'a');
	if (!str)
		return (0);
	if (isemptyor_spacetab(str) == 1)
		return (free(str), 0);
	if (count_c(str, '\'') % 2 != 0 || count_c(str, '\"') % 2 != 0)
	{
		ft_printf_fd(2, "bash: syntax error: unclosed quotes\n");
		return (free(str), 1);
	}
	if (chck1op(str) == 1)
		return (free(str), 1);
	else if (chck2op(str) == 1)
		return (free(str), 1);
	if (ft_strcmp(str1, str) == 0)
		return (0);
	return (free(str), 0);
}
