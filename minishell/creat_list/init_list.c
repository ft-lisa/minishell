#include "../minishell.h"
void init_list2(t_list *list)
{
        list->cmd = NULL;
        list->index = -1;
        list->exe1 = -1;
        list->exe2 = -1;
        list->if_file1 = NULL;
        list->if_file2 = NULL;
        list->delim = NULL;
}

t_list* init_list(int count, char ***envp, char **argv, int argc)
{
    t_list *first;
    t_list *list;
    t_data  *data;

    first = malloc(sizeof(t_list));
    if(!first)
        exit(1);
    data = init_exe(envp, argv, argc, count);
    first->data = data;
    list = first;
    while (count--)
    {
        init_list2(list);
        list->data = data;
        if (count > 0)
        {
            list->next = malloc(sizeof(t_list));
            if(list->next == NULL)
                exit(1);
            list = list->next;    
        }
    }
    list->next = NULL;

    return(first);
}

t_list *creat_list(char* line, char ***envp, char **argv, int argc)
{
    int count;
    char** content_node;
    t_list *command;
    int i = 0;
    char *temp;

    if (all_space(line) == 1)
        return(NULL);
    if(check_operator(line) == 1)
        return(NULL);
    if (expand_vars(&line, envp) == -1)
        return (NULL);
    content_node = ft_split_ope_bis(line, '|');
    free(line);
    count = double_strlen(content_node);
    command = init_list(count, envp, argv, argc);
    while(content_node[i])
    {
        temp = content_node[i];
        content_node[i] = ft_strtrim(content_node[i], " ");
        free(temp);
        i++;
    }
    fill_ope_list(command, content_node);    
    fill_com_list(command, content_node);
    del_space(command);
    del_quotes(command);
    command->data->content = content_node;
    return (command);
}
