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
    int j;


    if (all_space(line) == 1)
        return(NULL);
    content_node = ft_split_txt(line);
    if(check_operator(content_node) == 0)
        return(NULL);
    content_node = ft_split_ope_bis(line, '|');
    // expand_vars(content_node, envp);
    count = double_strlen(content_node);
    command = init_list(count, envp, argv, argc);
    while(content_node[i])
    {
        content_node[i] = ft_strtrim(content_node[i], " ");
        i++;
    }
    fill_ope_list(command, content_node);    
    fill_com_list(command, content_node);
    del_space(command);
    del_quotes(command);
    command->data->content = content_node;
    return (command);
}
