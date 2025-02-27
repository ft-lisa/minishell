#include "../minishell.h"

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
        {
            tmp = new->cmd;
            new->cmd = ft_strtrim(new->cmd, " ");
            free(tmp);
        }   
            
        if (new->if_file1)
        {
            tmp = new->if_file1;
            new->if_file1 = ft_strtrim(new->if_file1, " ");
            free(tmp);
        }
            
        if (new->if_file2)
        {
            tmp  = new->if_file2;
            new->if_file2 = ft_strtrim(new->if_file2, " ");
            free(tmp);
        }
            
        if (new->delim)
        {
            while (new->delim[i] != NULL)
            {
                tmp = new->delim[i];
                new->delim[i] = ft_strtrim(new->delim[i], " ");
                free(tmp);
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