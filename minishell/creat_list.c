#include "minishell.h"

void fill_list(t_list *list, char** content)
{
    while (list != NULL)
    {
    }     
}
t_list* init_list(int count)
{
    t_list *first;
    t_list *list;

    first = malloc(sizeof(t_list));
    if(!first)
        exit(1); // on a malloc split, history, readline
    list = first;
    while (count--)
    {
        list->cmd = NULL;
        list->index = -1;
        list->exe1 = -1;
        list->exe2 = -1;

        list->if_file1 = NULL;
        list->if_file2 = NULL;
        list->next = malloc(sizeof(t_list));
        if(list->next == NULL)
            exit(1); // on a malloc split, history, readline, des node de la list
        list = list->next;
    }
    list->next = NULL;
    return(first);
}

int count_node(char* line)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while(line[i] != '\0')
    {
        if(line[i] == '|')
        {
            while((line[i] == '|' || line[i] == '<' || line[i] == '>') && line[i] != '\0')
                i++;
            count++;
        }
        i++;
    }
    return(count + 1);
}

// int erreur_operater(char** content_node)
// {
//     int i;
//     int j;
//     int txt;

//     i = 0;
//     j = 0;
//     txt = 0;
//     while(content_node[i] != NULL)
//     {
//         j = 0;
//         while (content_node[i][j])
//         {

//             i++;
//         }
//         i++;
//     }
// }

t_list creat_list(char* line)
{
    int count;
    char** content_node;
    t_list *command;
    int i = 0;

    
    count = count_node(line);
    content_node = ft_split(line);
    free(line);
    //erreur_operater(content_node);
    // while(content_node[i] != NULL)
    // {
    //     printf("%s\n", content_node[i]);
    //     i++;
    // }
    //printf("count = %d\n", count);
    command = init_list(count);
    fill_list(&command, content_node);
}