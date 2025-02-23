#include "../minishell.h"

char	**split_until(char *str, char c)
{
	int	i;
	int	size;
	char	**new;
    int j;

    i = 0;
    j = 0;
	size = 0;
    new = malloc(3 * sizeof(char*));
    if(!new)
        return(NULL);
	while (str[size] != c)
		size++;
	new[0] = malloc((size + 1) * sizeof(char));
    new[1] = malloc((strlen(str) - size + 1) * sizeof(char));
    new[2] = NULL;
	if (!new[0] || !new[1])
		return (NULL);
	while (i < size)
	{
		new[0][i] = str[i];
		i++;
	}
    new[0][i] = '\0';
    while(str[i] != '\0')
    {
        new[1][j] = str[i];
        i++;
        j++;
    }
    new[1][j] = '\0';
	return (new);
}

void fill_seven(t_list* new, char* content)
{
    char** split_txt;
    char** split;
    int i;
    int k;

    split_txt = ft_split_txt(content);
    i = 0;
    k = 0;
    new->delim = malloc((size_delim(split_txt, 0) + 1) * sizeof(char *));
    if(operator(split_txt[i]) == 7)
    {
        while(split_txt[i + 1])
        {
            if(operator(split_txt[i]) == 0)
                new->delim[k++] = split_txt[i];
            i++;
        }
        split = ft_split(split_txt[i], ' ');
        new->delim[k] = split[0];
        if(split[1])
            new->cmd = split[1];
    }
    else
    {
        new->cmd = split_txt[0];
        i++;
        while(split_txt[i])
        {
            if(operator(split_txt[i]) == 0)
                new->delim[k++] = split_txt[i];
            i++;
        }
    }
}

void fill_one_three(t_list* new, char* content)
{
    char** split_txt;
    char** split;
    int j = 0;

    split_txt = ft_split_txt(content);
        if(operator(split_txt[0]) == 1 || operator(split_txt[0]) == 3)
        {
            split = ft_split(split_txt[1], ' ');
            new->if_file2 = split[0];
            if(split[1])
                new->cmd = split[1];
        }
        else
        {
            new->cmd = split_txt[0];
            new->if_file2 = split_txt[2];
        }
}

void fill_six(t_list* new, char* content)
{
    char** split_txt;
    char** split;

    split_txt = ft_split_txt(content);
        if(operator(split_txt[0]) == 6)
        {
            split = ft_split(split_txt[1], ' ');
            new->if_file1 = split[0];
            if(split[1])
                new->cmd = split[1];
        }
        else
        {
            new->cmd = split_txt[0];
            new->if_file1 = split_txt[2];
        }
}

void fill_com_list(t_list *list, char** content)
{
    char** split;
    int j;
    t_list *new;

    new = list;
    j = 0;
    while(content[j])
    {
        if((new->exe1 == 4 || new->exe1 == 5) && (new->exe2 == 2 || new->exe2 == 0))
            new->cmd = content[j];
        if((new->exe1 == 6 || new->exe1 == 7) && (new->exe2 == 1 || new->exe2 == 3))
        {
            split = split_until(content[j], '>');
            printf("%s\n", split[0]);
            printf("%s\n", split[1]);
            if(new->exe1 == 6)
                fill_six(new, split[0]);
            else
                fill_seven(new, split[0]);
            fill_one_three(new, split[1]);
        }
        else
        {
            if(new->exe1 == 6)
                fill_six(new, content[j]);
            if(new->exe1 == 7)
                fill_seven(new, content[j]);
            if(new->exe2 == 1 ||new->exe2 == 3)
                fill_one_three(new, content[j]);
        }
        j++;
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
    int j;
    t_list *new;

    j = 0;
    new = list;
    while(content[j])
    {
        new->index = j;
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
