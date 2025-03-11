#include "../minishell.h"

char* del_space2(char* str, t_list* pip)
{
    char* tmp;

    if(str == NULL)
        return(NULL);
    tmp = str;
    str = ft_strtrim(str, " ");
    free(tmp);
    if (!str)
        (free_pip(pip), exit(1));
    return(str);
}

void del_space(t_list *command)
{
    t_list *new;
    int i;
    char* tmp;

    new = command;
    while(new)
    {
        i = 0;
        if (new->cmd)
            new->cmd = del_space2(new->cmd, command);
        if (new->if_file1)
            new->if_file1 = del_space2(new->if_file1, command);
        if (new->if_file2)
            new->if_file2 = del_space2(new->if_file2, command);
        if (new->delim)
        {
            while (new->delim[i] != NULL)
            {
                tmp = new->delim[i];
                new->delim[i] = del_space2(new->delim[i], command);
                i++;
            }        
        }    
        new = new->next;
    }
}
void del_quotes(t_list *command)
{
    t_list *new;
    int i;
    new = command;
    while (new)
    {
        i = 0;
        new->if_file1 = del_c(new->if_file1, '"');
        new->if_file1 = del_c(new->if_file1, '\'');
        new->if_file2 = del_c(new->if_file2, '"');
        new->if_file2 = del_c(new->if_file2, '\'');
        if (new->delim)
        {
            while (new->delim[i] != NULL)
            {
                new->delim[i] = del_c(new->delim[i], '"');
                new->delim[i] = del_c(new->delim[i], '\'');
                i++;
            }
        }
        new = new->next;
    }
    
}
