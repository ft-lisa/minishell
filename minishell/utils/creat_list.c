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
                exit(1);
            list = list->next;    
        }
    }
    list->next = NULL;

    return(first);
}

int	replace_str(char **mainstr, char *before, char *after, int index)
{
	char	*new;
	int	i;
	int	len_a;
	int	len_b;

	i = 0;
	len_a = 0;
	if (after)
		len_a = ft_strlen(after);
	if (before == NULL)
		return (-1);
	len_b = ft_strlen(before);
	new = malloc ((ft_strlen((*mainstr)) - len_b + len_a  + 1) * sizeof(char));
	while(i < index)
	{
		new[i] = (*mainstr)[i];
		i++;
	}
	i = 0;
	while(after[i])
	{
		new[index + i] = after[i];
		i++;
	}
	while((*mainstr)[index + len_b])
	{
		new[index + len_a] = (*mainstr)[index + len_b];
		index++;
	}
	new[index + len_a] = '\0';
	free(*mainstr);
	*mainstr = new;
	return (0);
}

int	expand(char *cmd, char ***env)
{
	char	*new;
	char	*temp;
	char	*temp2;
	int	i;

	i = 0;
	while (cmd[i] && cmd[i] != '$')
		i++;
	temp = copy_until_one(cmd + i + 1, "<>|$\"");
	if (isin_2d_equal((*env), temp) == 1)
	{
		
	}
}

int 	expand_vars(char **cmd, char ***env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd[j])
	{

	}

}

t_list *creat_list(char* line, char ***envp, char **argv, int argc)
{
    int count;
    char** content_node;
    t_list *command;
    int i = 0;

    content_node = ft_split_ope_bis(line, '|');
    expand_var(content_node, envp);


    count = str_len_2d(content_node);
    command = init_list(count, envp, argv, argc);
    fill_ope_list(command, content_node);
    fill_com_list(command, content_node);
    fill_file_list(command, content_node);
    del_space(command);
    del_quotes(&command->delim);
    command->data->content = content_node;
    //fill_list(&command, content_node);
    return (command);
}
