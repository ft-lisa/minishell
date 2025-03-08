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

int	no_env_init(char ***envp)
{
	char	*temp;
	char	*path;
	
	path = pwd2((t_list *)"");
	if (path)
	{
		temp = ft_strjoin("PWD=", path);
		add_last_2d(envp, temp);
		free(temp);
		free(path);
	}
	add_last_2d(envp, "SHLVL=1");
	add_last_2d(envp, "_=/usr/bin/env");
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
    if (data == NULL)
        (free(first), exit (1));
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
                free_list(first);
            list = list->next;    
        }
    }
    list->next = NULL;
    return(first);
}

int     check_line(char **line, char ***envp, int error)
{
    if (all_space(*line) == 1)
        return (1);
    if (open_only_one_quote(*line) == 1)
        return (1);
    if (check_operator(*line) == 1)
        return (1);
    if (expand_vars(line, envp, error) == -1)
        return (1);
    if (isemptyor_spacetab(*line) == 1)
        return (1);
    return (0);
}

t_list *creat_list(char* line, char ***envp, char **argv, int argc)
{
    int count;
    char** content_node;
    t_list *command;
    int i = 0;
    char *temp;

    content_node = ft_split_ope_bis(line, '|', 0, 0);
    free(line);
    if (content_node == NULL)
        exit(1);
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
