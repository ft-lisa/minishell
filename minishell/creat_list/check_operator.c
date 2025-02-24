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
    else if (isin("<", temp[0]) && temp[1] == '<' && !temp[2])
        (ft_printf_fd(2, "bash: syntax error near unexpected token `newline'\n"), i++);
    else if (isin(">", temp[0]) && temp[1] == '>' && !temp[2])
        (ft_printf_fd(2, "bash: syntax error near unexpected token `newline'\n"), i++);
    free(temp);
    return (i);
    
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
    if (temp[1] && temp[0] == temp[1] && (temp[0] == '<' || temp[0] == '>'))
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
                check = isconsecutive_ops1(str, op);
        }
    return (check);
}

int     chck2op(char *str)
{
    char *temp;

    temp = ft_strtrim(str, " ");
    if (isconsecutive_opsloop(str, "<<") == 1)
        return (1);
    else if (isconsecutive_opsloop(str, "<") == 1)
        return (1);
    else if (isconsecutive_opsloop(str, ">") == 1)
        return (1);
    else if (isconsecutive_opsloop(str, ">>") == 1)
        return (1);
    else if (isconsecutive_opsloop(str, "|") == 1)
        return (1);
    else if (isin("<>|", temp[ft_strlen(temp) - 1]) == 1 && chck2op(str) == 0) // ADD IS NOT ERROR BEFORE
    {
        (ft_printf_fd(2, "bash: syntax error near unexpected token `newline'\n"));
        return (free(temp), 1);
    }
    return (0);
}


int check_operator(char* str)
{
    if (chck1op(str) == 1)
        return (1);
    else if (chck2op(str) == 1)
        return (1);
    return (0);
}
