# include "../minishell.h"

int     chck1op(char *str)
{
    char *temp;
    int i;

    temp = ft_strtrim(str, " ");
    i = 0;
    if (isin("<>", temp[0]) && !temp[1])
        (ft_printf_fd(2, "bash: syntax error near unexpected token `newline'\n"), i++);
    else if (isin("|", temp[0]) && !temp[1])
        (ft_printf_fd(2, "bash: syntax error near unexpected token `|'\n"), i++);
	else if (temp[1] &&  isin("|", temp[0]) && isin("|", temp[1]) && !temp[2])
        (ft_printf_fd(2, "bash: syntax error near unexpected token `||'\n"), i++);
    else if (isin("<", temp[0]) && temp[1] == '<' && !temp[2])
        (ft_printf_fd(2, "bash: syntax error near unexpected token `newline'\n"), i++);
    else if (isin(">", temp[0]) && temp[1] == '>' && !temp[2])
        (ft_printf_fd(2, "bash: syntax error near unexpected token `newline'\n"), i++);
    free(temp);
    return (i);
    
}

int     isconsecutive_ops1_index(char *str, char *op)
{
    char *temp;
    int i;

    temp = ft_strstr(str, op);
    i = ft_strlen(op);
    if (!temp || temp[0] == '\0')
        return (ft_strlen(str));
	if (temp[1] && temp[0] == temp[1] && i == 1 && (temp[0] == '<' || temp[0] == '>'))
        temp = temp + 1;
    while (temp[i] &&  temp[i] == ' ')
        i++;
    if (temp[i] && temp[i + 1] && isin("|<>", temp[i]) == 1 && isin("|<>", temp[i + 1]) == 0)
        return (ft_strlen(str) - ft_strlen(temp));
    else if (temp[i] && !temp[i + 1] && isin("|<>", temp[i]) == 1)
		return (ft_strlen(str) - ft_strlen(temp));
    else if (temp[i] && temp[i + 1] && isin("|<>", temp[i]) == 1 && isin("|<>", temp[i + 1]) == 1)
		return (ft_strlen(str) - ft_strlen(temp));
    return (ft_strlen(str));
}

int     isconsecutive_opsloop_index(char *str, char *op)
{
    int i = 0;
    char *temp;
    int check;
	int len ;
	
	len = ft_strlen(str);
    temp = ft_strstr(str, op);
    if (!temp || temp[0] == '\0')
        return (ft_strlen(str));
    check = isconsecutive_ops1_index(str, op);
        while(temp && temp[0] && check == len)
        {
			if (!temp[1])
				break;
            temp = ft_strstr(temp + 2, op);
            if (temp)
                check = isconsecutive_ops1_index(temp, op);
        }
    return (check);
}

int     chck2op_type(char *str)
{
	int	*i;
	int	j;
	int min;

	j = 0;
	i = malloc(5 * sizeof(int));
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
	free(i);
	return (min);
}

int     isconsecutive_ops1(char *str, char *op)
{
    char *temp;
    int i;
    int j;

    temp = ft_strstr(str, op);
    i = ft_strlen(op);
    j = 0;
    if (!temp || temp[0] == '\0')
        return (0);
	if (temp[1] && temp[0] == temp[1] && i == 1 && (temp[0] == '<' || temp[0] == '>'))
        temp = temp + 1;
    while (temp[i] &&  temp[i] == ' ')
        i++;
    if (temp[i] && temp[i + 1] && isin("|<>", temp[i]) == 1 && isin("|<>", temp[i + 1]) == 0)
        (ft_printf_fd(2, "bash: syntax error near unexpected token `%c'\n", temp[i]), j++);
    else if (temp[i] && !temp[i + 1] && isin("|<>", temp[i]) == 1)
        (ft_printf_fd(2, "bash: syntax error near unexpected token `%c'\n", temp[i]), j++);
    else if (temp[i] && temp[i + 1] && isin("|<>", temp[i]) == 1 && isin("|<>", temp[i + 1]) == 1)
        (ft_printf_fd(2, "bash: syntax error near unexpected token `%c%c'\n", temp[i], temp[i + 1]), j++);
    return (j);
}

int     isconsecutive_opsloop(char *str, char *op)
{
    int i = 0;
    char *temp;
    int check;

    temp = ft_strstr(str, op);
    if (!temp || temp[0] == '\0')
        return (0);
    check = isconsecutive_ops1(str, op);
        while(temp && temp[0] && check == 0)
        {
            temp = ft_strstr(temp + 2, op);
            if (temp)
                check = isconsecutive_ops1(temp, op);
        }
    return (check);
}

int     chck2op(char *str)
{
    char	*temp;
	char	**op;
	int		i;

	i = chck2op_type(str);
	op = ft_split("<< >> < > |", ' ');
    temp = ft_strtrim(str, " ");
	if (isconsecutive_opsloop(str, op[i]) == 1)
        return (free(temp), cleanexit(op), 1);
    else if (isin("<>|", temp[ft_strlen(temp) - 1]) == 1)
    {
        (ft_printf_fd(2, "bash: syntax error near unexpected token `newline'\n"));
        return (free(temp), cleanexit(op), 1);
    }
    return (free(temp), cleanexit(op), 0);
}

char	*remove_biggest_quotes(char *str)
{
	char *temp;
	char *temp2;
	char *join;
	char del_q;

	if (ft_strchr(str, '\'') == NULL && ft_strchr(str, '\"') == NULL)
		return (ft_strdup(str));
	if (isin(str, '\'') == 1)
		del_q = '\'';
	if (isin(str, '\"') == 1)
		del_q = '\"';
	if ((isin(str, '\"') == 1)  && (isin(str, '\'') == 1))
		if (ft_strlen(ft_strchr(str, '\'')) > ft_strlen(ft_strchr(str, '\"')))
			del_q = '\'';
	temp = copy_until(str, del_q);
	temp2 = ft_strchr(str, del_q) + 1;
	while (temp2 && temp2[0])
	{
		if(!ft_strchr(temp2, del_q))
			break;
		temp2 = ft_strchr(temp2, del_q) + 1;
	}
	join = ft_strjoin(temp, temp2);
	free(temp);
	return (join);
}


int check_operator(char* str1)
{
	char *str;

	str = remove_biggest_quotes(str1);
	printf("%s\n", str);
	if (isin(str, '\'') == 1 || isin(str, '\"') == 1)
		{
			ft_printf_fd(2, "bash: syntax error: unclosed quotes\n");
			return(free(str), 1);
		}
    if (chck1op(str) == 1)
        return (free(str), 1);
    else if (chck2op(str) == 1)
        return (free(str), 1);
    return (0);
}
