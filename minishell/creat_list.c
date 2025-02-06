#include "minishell.h"

int operator (char* txt)
{
    int i;

    i = 0;
    
    if (txt[i] == '|')
        return(2);
    if (txt[i] == '>' && txt[i + 1] == '>')
        return(3);
    if (txt[i] == '>')
        return(1);
    if (txt[i] == '<')
      return(6);
    return(0);
}

void print_list(t_list *lst)
{
    while (lst)
    {
        printf("Command: %s\n", lst->cmd ? lst->cmd : "(null)");
        printf("Index: %d\n", lst->index);
        printf("Exe1: %d\n", lst->exe1);
        printf("Exe2: %d\n", lst->exe2);
        printf("If File1: %s\n", lst->if_file1 ? lst->if_file1 : "(null)");
        printf("If File2: %s\n", lst->if_file2 ? lst->if_file2 : "(null)");
        printf("--------------------\n");
        lst = lst->next;
    }
}


char	*ft_strdup(const char *source)
{
	char	*dest;
	int		len;
	int		i;

	i = 0;
	len = strlen(source);
	dest = malloc(len * sizeof(char) + 1);
	if (dest == NULL)
		return (NULL);
	while (source[i] != '\0')
	{
		dest[i] = source[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void fill_file_list(t_list *list, char** content)
{
    t_list *new;
    int     j;

    new = list;
    j = 0;
    while (new != NULL)
    {
        if(new->exe1 == 6)
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

int fill_com_list2(t_list *new, char** content, int j)
{
    int i;
    char** str;

    i = 0;
    if(new->exe1 == 6 && operator(content[0]) == 6)
    {
        str = ft_split(content[1], ' ');
        new->cmd = str[0];
        new->if_file1 = str[1];
        j = 4;
        while (str[i])
        {
            free(str[i]);
            i++;
        }
        free(str);
    }
    if(new->exe1 == 6 && operator(content[1]) == 6)
    {
        new->cmd = content[0];
        new->if_file1 = content[2];
        j = 4;
    }
    return(j);
}

void fill_com_list(t_list *list, char** content)
{
    t_list *new;
    int     j;
    char** str;
    int i;

    new = list;
    j = 0;
    i = 1;
    while (new != NULL)
    {
        new->index = i++;
        if (new->exe1 == 4)
        {
            new->cmd = content[j];
            j = j + 2;
        }
        if (new->exe1 == 5)
        {    
            new->cmd = content[j];
            j = j + 2;
        }
        j = fill_com_list2(new, content, j);
        new = new->next;
    }
}

void fill_ope_list(t_list *list, char** content)
{
    t_list *new;
    int j;
    int ope;

    new = list;
    j = 0;
    while (new != NULL)
    {
        ope = 0;
        while(ope == 0 && content[j] != NULL)
            ope = operator(content[j++]);    
        if (ope > 3)
            new->exe1 = ope;
        if (ope == 6)
        {
            ope = 0;
            while(ope == 0 && content[j] != NULL)
                ope = operator(content[j++]);  
        }
        if (ope < 4)
            new->exe2 = ope;
        if (ope == 2)
        {
            if (new->next != NULL)
            new->next->exe1 = 5;
            
        }
        if (new->exe1 == -1)
                new->exe1 = 4;
        new = new->next;
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
    content_node = ft_split_txt(line);
    free(line);
    //erreur_operater(content_node);
    // while(content_node[i] != NULL)
    // {
    //     printf("%d :%s\n", i, content_node[i]);
    //     i++;
    // }
    //printf("count = %d\n", count);
    command = init_list(count);
    fill_ope_list(command, content_node);
    fill_com_list(command, content_node);
    fill_file_list(command, content_node);
    print_list(command);
    //fill_list(&command, content_node);
}