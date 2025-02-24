# include "../minishell.h"

int count_puts (char* str)
{
    int i;
    int less;
    int more;

    i = 0;
    less = 0;
    more = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '<')
        {
            less++;
            if (more != 0)
            {
                while(str[i] == '<' && str[i] != '\0')
                {
                    less++;
                    i++;
                }
                return(-less - 1);
            }
        }    
        if (str[i] == '>')
        {
            more++;
            if (less != 0)
            {
                while(str[i] == '>' && str[i] != '\0')
                {
                    more++;
                    i++;
                }
                return(more + 1);
            }
        }
        if (more == 3 && str[i + 1] == '>')
            return(4);
        else if (more == 3)
            return(3);
        if (less == 3 && str[i + 1] == '<')
            return(-4);
        else if (less == 3)
            return(-3); 
        i++;
    }

}

int count_puts_two (char* str)
{
    int i;

    i = 0;
    if (str[i] == '<')
    {
        while(str[i] && str[i] == '<')
            i++;
        return(-i);
    }
    if (str[i] == '>')
    {
        while(str[i] && str[i] == '>')
            i++;
        return(i);
    }
}


int check_files_puts(char** str)
{
    int j;
    int num_puts;

    j = 0;
    num_puts = 0;
    while(str[j])
    {
        
        
        if((operator(str[j]) == 1 || operator(str[j]) == 3 || operator(str[j]) == 6 || operator(str[j]) == 7) && !str[j + 1])
            return(printf("bash: syntax error near unexpected token `newline'\n"), 0);

        j++;
    }
    return(1);
}

int check_pipe(char** split, char** ope, int i, int j) // good
{
    int num_pipes;

    num_pipes = 0;
    if (i == 0)
    {
        if (split[j - 1] == NULL)
        {
            num_pipes = count_pipes(ope[i]);
            if(num_pipes == 2)
                return(printf("bash: syntax error near unexpected token `|'\n"), 0);
            if(num_pipes > 2)
                return(printf("bash: syntax error near unexpected token `||'\n"), 0);
            return(1);
        }
            
    }
    num_pipes = count_pipes(ope[i]) - 1;
    if(num_pipes == 1)
        return(printf("bash: syntax error near unexpected token `|'\n"), 0);
    if(num_pipes > 1)
        return(printf("bash: syntax error near unexpected token `||'\n"), 0);
    return(1);
}

int check_puts(char** split, char** ope, int i, int j) // good
{
    int num_puts;

    num_puts = 0;
    num_puts = count_puts(ope[i]);
    if (num_puts == -3)
        return(printf("bash: syntax error near unexpected token `<'\n"), 0);
    if (num_puts < -3)
        return(printf("bash: syntax error near unexpected token `<<'\n"), 0);
    if (num_puts == 3)
        return(printf("bash: syntax error near unexpected token `>'\n"), 0);
    if (num_puts > 3)
        return(printf("bash: syntax error near unexpected token `>>'\n"), 0);
    if(ope[i + 1] == NULL)
    {
        if(split[j + 1] == NULL)
        {
            return(printf("bash: syntax error near unexpected token `newline'\n"), 0);
        }
        j++;
        while (all_space(split[j]) == 1 && split[j])
            j++;
        if(operator(split[j]) == 5 || operator(split[j]) == 8)
        {
            num_puts = count_pipes(split[j]);
            if(num_puts == 1)
                return(printf("bash: syntax error near unexpected token `|'\n"), 0);
            if(num_puts > 1)
                return(printf("bash: syntax error near unexpected token `||'\n"), 0);
        }
        
        if(operator(split[j]) == 6 || operator(split[j]) == 7 || operator(split[j]) == 1 || operator(split[j]) == 3)
        {
            num_puts = count_puts_two(split[j]);
            if (num_puts == -1)
                return(printf("bash: syntax error near unexpected token `<'\n"), 0);
            if (num_puts <= -2)
                return(printf("bash: syntax error near unexpected token `<<'\n"), 0);
            if (num_puts == 1)
                return(printf("bash: syntax error near unexpected token `>'\n"), 0);
            if (num_puts >= 2)
                return(printf("bash: syntax error near unexpected token `>>'\n"), 0);
        }
        return(1);
    }
    if(operator(ope[i + 1]) == 5 || operator(ope[i + 1]) == 8 )
    {
        num_puts = count_pipes(ope[i + 1]);
        if(num_puts == 1)
            return(printf("bash: syntax error near unexpected token `|'\n"), 0);
        if(num_puts > 1)
            return(printf("bash: syntax error near unexpected token `||'\n"), 0);
    }
    else
    {
        num_puts = count_puts_two(ope[i + 1]);
        if (num_puts == -1)
            return(printf("bash: syntax error near unexpected token `<'\n"), 0);
        if (num_puts <= -2)
            return(printf("bash: syntax error near unexpected token `<<'\n"), 0);
        if (num_puts == 1)
            return(printf("bash: syntax error near unexpected token `>'\n"), 0);
        if (num_puts >= 2)
            return(printf("bash: syntax error near unexpected token `>>'\n"), 0);
    }
        
}

int check_operator(char** split) // good
{
    int j;
    int i;
    char** ope;
    int check;

    j = 0;
    check = 1;
     j= 0;
    while (split[j])
    {
        if(operator(split[j]) != 0)
        {
            ope = ft_split_ope(split[j]);
            i = 0;
            while(ope[i])
            {
                if (operator(ope[i]) == 2)
                    check = check_pipe(split, ope, i, j);
                if (operator(ope[i]) == 8)
                    return(printf("bash: syntax error near unexpected token `&'\n"), 0);
                if (operator(ope[i]) == 6 || operator(ope[i]) == 7 || operator(ope[i]) == 1 || operator(ope[i]) == 3)
                    check = check_puts(split, ope, i, j);
                if (check == 0)
                    return(0);
                i++;
            }
        }
        j++;
    }
    return(1);
}