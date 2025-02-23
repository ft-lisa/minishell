#include "../minishell.h"

t_list* init_list(int count, char **envp, char **argv, int argc)
{
    t_list *first;
    t_list *list;
    t_data  *data;

    first = malloc(sizeof(t_list));
    if(!first)
        exit(1); // on a malloc split, history, readline
    data = init_exe(envp, argv, argc, count);
    first->data = data;
    list = first;
    while (count--)
    {
        list->cmd = NULL;
        list->index = -1;
        list->exe1 = -1;
        list->exe2 = -1;
        list->if_file1 = NULL;
        list->if_file2 = NULL;
        list->data = data;
        list->delim = NULL;
        if (count > 0)
        {
            list->next = malloc(sizeof(t_list));
            if(list->next == NULL)
                exit(1); // on a malloc split, history, readline, des node de la list
            list = list->next;    
        }
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
    if (line == NULL)
        exit(0);
    while(line[i] != '\0')
    {
        if(line[i] == '"' || line[i] == '\'' )
            i = pass_quote1(line[i], line, i + 1);
        //printf("%c\n", line[i]);
        if(!line[i])
            return(count + 1);
        if(line[i] == '|')
        {
            while((line[i] == '|' || line[i] == '<' || line[i] == '>') && line[i] != '\0')
                i++;
            count++;
            if (line[i] == '\0')
                return(count + 1);
        }
        i++;
    }
    return(count + 1);
}



t_list *creat_list(char* line, char **envp, char **argv, int argc)
{
    int count;
    char** content_node;
    t_list *command;
    int i = 0;
    int j;


    if (all_space(line) == 1)
        return(NULL);
    //printf("||||count||||%d\n\n", count); // print_info
    content_node = ft_split_ope_bis(line, '|');
    count = double_strlen(content_node);
    // if (check_operator(content_node) == 0)
    //    return(NULL);
    command = init_list(count, envp, argv, argc);
    while(content_node[i])
    {
        content_node[i] = ft_strtrim(content_node[i], " ");
        i++;
    }
    fill_ope_list(command, content_node);    
    fill_com_list(command, content_node);
    print_list(command);
    return(NULL);
    fill_file_list(command, content_node);
    del_space(command);
    // printf("delim |%s| \n\n", command->delim); // print_info
    del_quotes(command);
    command->data->content = content_node;
    // print_list(command); // print_info
    //fill_list(&command, content_node);
    return (command);
}
