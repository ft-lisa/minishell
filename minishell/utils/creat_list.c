#include "../minishell.h"

void fill_file_list(t_list *list, char** content)
{
    t_list *new;
    int     j;

    new = list;
    j = 0;
    while (new != NULL)
    {
        if(new->exe1 == 6 || new->exe1 == 7)
            j = 4;
        if(new->exe1 == 4 || new->exe1 == 5)
            j = j + 2;
        if(new->exe2 == 1 || new->exe2 == 3)
        {
            //j = j + 2;
            new->if_file2 = content[j];
        }                    
        new = new->next;
    }
}

int fill_com_list2(t_list *new, char** content, int j, int max)
{
    int i;
    int k;
    char** str;
    int ope;

    i = 0;
    k = 0;
     printf("|%s|\n", content[j]);
     printf("|%s|\n", content[j + 1]);
    // printf("|%s|\n", content[j + 2]);
    // printf("|%s|\n", content[j - 2]);
    if(all_space(content[j]) == 1)
        j++;
    if(new->exe1 == 6 && operator(content[0]) == 6)
    {
        printf("coucou : %s\n", content[j]);
        str = ft_split(content[j + 1], ' ');
        if (str[1])
            new->cmd = str[1];
        new->if_file1 = str[0];
        j = j + 4;
        if (j > max);
            return (-1);
        return(j);
    }
    if(new->exe1 == 6 && operator(content[j]) == 6  && (operator(content[j - 2]) != 0))
    {
        printf("coucou : %s\n", content[j]);
        str = ft_split(content[j + 1], ' ');
        if (str[1])
            new->cmd = str[1];
        new->if_file1 = str[0];
        j = j + 4;
        if (j > max);
            return (-1);
        return(j);
    }
    // if(new->exe1 == 7 && operator(content[j + 1]) == 7  && (operator(content[j - 1]) != 0 || operator(content[j - 1]) != -1))
    // {
    //     j++;
    //     new->delim = malloc((size_delim(content, j) + 1) * sizeof(char *));
    //     new->delim[k] = content[j];
    //     k++;
    //     j++;
    //     ope = 0;
    //     while((ope == 0 || ope == 7) && content[j] != NULL)
    //     {
    //         ope = operator(content[j]);
    //         if (ope == 0)
    //         {
    //             new->delim[k] = content[j];
    //             k++;
    //         }
                
    //         j++;
    //     }    
    //     new->delim[k] = NULL;
    //     return(j);
    // }
    new->cmd = content[j];
    j = j + 2;
    if (j > max)
        return (-1);
    if (new->exe1 == 6)
        new->if_file1 = content[j];
    if(new->exe1 == 7)
    {
        new->delim = malloc((size_delim(content, j) + 1) * sizeof(char *));
        new->delim[k] = content[j];
        k++;
        j++;
        ope = 0;
        while((ope == 0 || ope == 7) && content[j] != NULL)
        {
            ope = operator(content[j]);
            if (ope == 0)
            {
                new->delim[k] = content[j];
                k++;
            }
                
            j++;
        }    
        new->delim[k] = NULL;
        return(j);
    }
    return(j + 2);
}


void fill_com_list(t_list *list, char** content)
{
    t_list *new;
    int     j;
    char** str;
    int i;
    int max;

    max = double_strlen(content);
//    printf("MAX : %d", max);
    new = list;
    j = 0;
    i = 1;

    while (new != NULL)
    {
        new->index = i++;
        if (new->exe1 == 4)
        {
            if(operator(content[j]) == 0 )
                new->cmd = content[j];
            j = j + 2;
            if (j > max);
                return ;
        }
        if (new->exe1 == 5)
        {   
            printf("wwww %s\n", content[j]);
            new->cmd = content[j];
            printf("qqqq %s\n", new->cmd);
            j = j + 2;
            if (j > max);
                return ;
        }
        j = fill_com_list2(new, content, j, max);
        if (j == -1)
            return ;
        new = new->next;
    }
}

int search_exe1(char* content)
{
    int i;

    i = 0;
    while (content[i])
    {
        if(content[i] =='<')
        {
            if(content[i + 1] == '<')
                return(7);
            return(6);
        }
        i++;
    }
    return(4);
}
int search_exe2(char* content)
{
    int i;

    i = 0;
    while(content[i])
    {
        if(content[i] =='>')
        {
            if(content[i + 1] == '>')
                return(3);
            return(1);
        }
        i++;
    }
    return(0);
}

void fill_ope_list(t_list *list, char** content)
{
    int i;
    int j;
    t_list *new;

    i = 0;
    j = 0;
    new = list;
    while(content[j])
    {
        if(content [j + 1] != NULL)
        {
            new->exe2 = 2;
            new->next->exe1 = 5;
        }
        if(new->exe1 == -1 || (search_exe1(content[j]) != 4 && new->exe1 == 5))
        new->exe1 = search_exe1(content[j]);
        if(new->exe2 == -1 || (search_exe2(content[j]) != 0 && new->exe2 == 2))
            new->exe2 = search_exe2(content[j]);
        new = new->next;
        j++;
    }
}