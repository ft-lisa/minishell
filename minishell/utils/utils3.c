#include "../minishell.h"

int pass_quote1(char quote, char* str, int i)
{
    while(str[i] != quote && str[i] != '\0')
        i++;
    return(i + 1);
}

int size_delim(char **content, int j)
{
    int num = 0;
    while(operator(content[j]) == 0 || operator(content[j]) == 7)
    { 
        if(operator(content[j]) == 7);
            num++;
        j++;
    }
    return(num);
}

int double_strlen(char **content)
{
    int i;

    i = 0;
    while(content[i])
        i++;
    return(i);
}
int all_space(char* line)
{
    int i;

    i = 0;
    if (line == NULL)
        return(-1);
    while(line[i] != '\0')
    {
        if (line[i] != ' ' && line[i] != '\t')
            return(0);
        i++;
    }
    return(1);
}
int count_pipes (char* str)
{
    int i;

    i = 0;
    if (str == NULL)
        return(i);
    while (str[i])
    {
        if(str[i] != '|')
            return(i);
        i++;
    }
    return(i);
}