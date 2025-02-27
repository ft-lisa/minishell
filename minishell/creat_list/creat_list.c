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
        free(split_txt[i]);
        new->delim[k] = split[0];
        new->delim[k + 1] = NULL;
        if(split[1])
            new->cmd = ft_strdup(split[1]);
        cleanexit(split);
    }
    else
    {
        new->cmd = ft_strdup(split_txt[0]);
        i++;
        while(split_txt[i])
        {
            if(operator(split_txt[i]) == 0)
                new->delim[k++] = split_txt[i];
            i++;
        }
        new->delim[k++] = NULL;
    }
    cleanexit(split_txt);
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
            new->if_file2 = ft_strdup(split[0]);
            if(split[1])
                new->cmd = ft_strdup(split[1]);
            cleanexit(split);
        }
        else
        {
            new->cmd = ft_strdup(split_txt[0]);
            new->if_file2 = ft_strdup(split_txt[2]);
        }
        cleanexit(split_txt);
}

void fill_six(t_list* new, char* content)
{
    char** split_txt;
    char** split;

    split_txt = ft_split_txt(content);
        if(operator(split_txt[0]) == 6)
        {
            split = ft_split(split_txt[1], ' ');
            new->if_file1 = ft_strdup(split[0]);
            if(split[1])
                new->cmd = ft_strdup(split[1]);
            cleanexit(split);
        }
        else
        {
            new->cmd = ft_strdup(split_txt[0]);
            new->if_file1 = ft_strdup(split_txt[2]);
        }
        cleanexit(split_txt);
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
            new->cmd = ft_strdup(content[j]);
        if((new->exe1 == 6 || new->exe1 == 7) && (new->exe2 == 1 || new->exe2 == 3))
        {
            split = split_until(content[j], '>');
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

void fill_ope_list(t_list *list, char** content)
{
    int j;
    t_list *new;

    j = 0;
    new = list;
    while(content[j])
    {
        new->index = j + 1;
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
