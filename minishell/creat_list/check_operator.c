/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lismarti <lismarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 10:53:33 by lismarti          #+#    #+#             */
/*   Updated: 2025/03/10 14:26:32 by lismarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	chck1op(char *str)
{
	char	*temp;
	int		i;

	if (str && str[0])
	{
		temp = ft_strtrim(str, " ");
		if (!temp)
			return(1);
	}	
	else
		return (0);
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
	free(temp);
	return (i);
}

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
	if (temp[i] && temp[i + 1] && isin("|<>", temp[i]) == 1 && isin("|<>",
			temp[i + 1]) == 0)
		(ft_printf_fd(2, "bash: syntax error near unexpected token `%c'\n",
				temp[i]), j++);
	else if (temp[i] && !temp[i + 1] && isin("|<>", temp[i]) == 1)
		(ft_printf_fd(2, "bash: syntax error near unexpected token `%c'\n",
				temp[i]), j++);
	else if (temp[i] && temp[i + 1] && isin("|<>", temp[i]) == 1 && isin("|<>",
			temp[i + 1]) == 1)
		(ft_printf_fd(2, "bash: syntax error near unexpected token `%c%c'\n",
				temp[i], temp[i + 1]), j++);
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

int	chck2op(char *str)
{
	char	*temp;
	char	**op;
	int		i;

	if (str && str[0])
	{
		temp = ft_strtrim(str, " ");
		if (!temp)
			return(1);
	}
		
	else
		return (0);
	i = chck2op_type(str);
	op = ft_split("<< >> < > |", ' ');
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

char	*remove_first_quotes(char *str)
{
	char	*temp;
	char	*temp2;
	char	*join;
	char	del_q;

	if (ft_strchr(str, '\'') == NULL && ft_strchr(str, '\"') == NULL)
		return (str);
	del_q = pick_quote(str);
	temp = copy_until(str, del_q);
	if (!temp)
		return(NULL);
	temp2 = ft_strchr(str, del_q) + 1;
	temp2 = ft_strchr(temp2, del_q) + 1;
	if (temp && temp2 && temp[0] && temp2[0])
	{
		temp2 = ft_strjoin("Z", temp2);
		if (!temp2)
			return(NULL);
		join = ft_strjoin(temp, temp2);
		free(temp2);
	}
	else if (!temp || !temp[0])
	{
		join = ft_strdup(temp2);
		if (!join)
			return (NULL);
	}	
	else
	{
		temp2 = ft_strjoin(temp, "Z");
		free(temp);
		return (temp2);
	}
	free(temp);
	return (join);
}

char	*remove_all_quotes(char *str)
{
	char	*temp;
	char	*temp2;
	char	*join;
	char	del_q;

	del_q = pick_quote(str);
	temp = ft_strdup(str);
	if (!temp)
		return(NULL);
	while (count_c(temp, '\'') > 0 || count_c(temp, '\"') > 0)
	{
		temp2 = remove_first_quotes(temp);
		if (!temp2)
			return (free (temp), NULL);
		if (ft_strchr(temp2, '\'') == NULL && ft_strchr(temp2, '\"') == NULL)
			return (free(temp), temp2);
		free(temp);
		temp = ft_strdup(temp2);
		free(temp2);
		if (!temp)
			return(NULL);
		del_q = pick_quote(temp);
		if (count_c(temp, del_q) == 1)
			return (temp);
	}
	free(temp);
	return (str);
}

int	check_operator(char *str1)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = remove_all_quotes(str1);
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
