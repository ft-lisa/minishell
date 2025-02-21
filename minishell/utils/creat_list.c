#include "../minishell.h"

int operator(char* txt)
{
    int i;

    i = 0;
    if(txt == NULL)
        return(-1);
    if (txt[i] == '|')
        return(2);
    if (txt[i] == '>' && txt[i + 1] == '>')
        return(3);
    if (txt[i] == '>')
        return(1);
    if (txt[i] == '<' && txt[i + 1] == '<')
        return(7);
    if (txt[i] == '<')
      return(6);
    if (txt[i] == '&')
        return(8);
    return(0);
}

void print_list(t_list *lst)
{
    int i;
    while (lst)
    {
        i = 0;
        printf("Command: |%s|\n", lst->cmd ? lst->cmd : "(null)");
        printf("Nbr commands: |%d|\n", lst->data->n_cmd);
        printf("Index: %d\n", lst->index);
        printf("Exe1: %d\n", lst->exe1);
        printf("Exe2: %d\n", lst->exe2);
        printf("If File1: |%s|\n", lst->if_file1 ? lst->if_file1 : "(null)");
        printf("If File2: |%s|\n", lst->if_file2 ? lst->if_file2 : "(null)");
        if(lst->delim)
        {
            while(lst->delim[i] != NULL)
            {
                printf("If delim: |%s|\n", lst->delim[i] ? lst->delim[i] : "(null)");
                i++;
            }            
        }

            
        printf("--------------------\n");
        lst = lst->next;
    }
}

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

int pass_quote1(char quote, char* str, int i)
{
    while(str[i] != quote && str[i] != '\0')
        i++;
    return(i + 1);
}

int size_delim(char **content, int j)
{
    int num = 0;
    while(operator(content[j]) == 0 || operator(content[j]) == 7)
    { 
        if(operator(content[j]) == 7);
            num++;
        j++;
    }
    return(num);
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
int double_strlen(char **content)
{
    int i;

    i = 0;
    while(content[i])
        i++;
    return(i);
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
        if(ope == 7)
        {
            while((ope == 0 || ope == 7) && content[j] != NULL)
            {
                ope = operator(content[j++]);   
            }
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
void del_space(t_list *command)
{
    t_list *new;
    int i;
    

    new = command;
    while(new)
    {
        i = 0;
        if (new->cmd)
            new->cmd = ft_strtrim(new->cmd, " ");
        if (new->if_file1)
            new->if_file1 = ft_strtrim(new->if_file1, " ");
        if (new->if_file2)
            new->if_file2 = ft_strtrim(new->if_file2, " ");
        if (new->delim)
        {
            while (new->delim[i] != NULL)
            {
                new->delim[i] = ft_strtrim(new->delim[i], " ");
                i++;
            }
                
        }
            
        new = new->next;
    }
}
void del_quotes(t_list *command)
{
    t_list *new;
    int i;
    new = command;
    while (new)
    {
        i = 0;
        new->if_file1 = del_c(new->if_file1, '"');
        new->if_file1 = del_c(new->if_file1, '\'');
        new->if_file2 = del_c(new->if_file2, '"');
        new->if_file2 = del_c(new->if_file2, '\'');
        if (new->delim)
        {
            while (new->delim[i] != NULL)
            {
                new->delim[i] = del_c(new->delim[i], '"');
                new->delim[i] = del_c(new->delim[i], '\'');
                i++;
            }
        }
        new = new->next;
    }
}
int all_space(char* line)
{
    int i;

    i = 0;
    if (line == NULL)
        return(-1);
    while(line[i] != '\0')
    {
        if (line[i] != ' ')
            return(0);
        i++;
    }
    return(1);
}
int count_pipes (char* str)
{
    int i;

    i = 0;
    if (str == NULL)
        return(i);
    while (str[i])
    {
        if(str[i] != '|')
            return(i);
        i++;
    }
    return(i);
}



int check_pipes(char** content_nodes, t_list* command)
{
    int i;
    int num_pipes;
    t_list* new;

    i = 1;
    new = command;
    while(new)
    {
        if(new->exe2 == 2)
        {
            if(new->cmd == NULL)
            {
                num_pipes = count_pipes(content_nodes[i - 1]);
            }
            else
            {   
                num_pipes = count_pipes(content_nodes[i]) - 2;
            }
            if(num_pipes == 1)
                return(printf("bash: syntax error near unexpected token `|'\n"), 0);
            if(num_pipes > 1)
                return(printf("bash: syntax error near unexpected token `||'\n"), 0);
              
        }
        i = i + 2;
        new = new->next;  
    }
    return(1);
}

int count_puts (char* str)
{
    int i;
    int less;
    int more;

    i = 0;
    less = 0;
    more = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '<')
        {
            less++;
            if (more != 0)
            {
                while(str[i] == '<' && str[i] != '\0')
                {
                    less++;
                    i++;
                }
                return(-less - 1);
            }
        }    
        if (str[i] == '>')
        {
            more++;
            if (less != 0)
            {
                while(str[i] == '>' && str[i] != '\0')
                {
                    more++;
                    i++;
                }
                return(more + 1);
            }
        }
        if (more == 3 && str[i + 1] == '>')
            return(4);
        else if (more == 3)
            return(3);
        if (less == 3 && str[i + 1] == '<')
            return(-4);
        else if (less == 3)
            return(-3); 
        i++;
    }

}
int check_special_case(char* str)
{
    if (str[0] == '<' && str[1] == '>' && str[2] == '<' && str[3] == '>')
        return(1);
    return(0);
}

int count_puts_two (char* str)
{
    int i;

    i = 0;
    if (str[i] == '<')
    {
        while(str[i] && str[i] == '<')
            i++;
        return(-i);
    }
    if (str[i] == '>')
    {
        while(str[i] && str[i] == '>')
            i++;
        return(i);
    }
}


int check_pppputs(char** str)
{
    int i;
    int j;
    int num_puts;

    i = 0;
    j = 0;
    num_puts = 0;
    
    while (str[j])
    {
        if(strlen (str[j]) >= 4 && operator(str[j]) == 6)
        {
            if (check_special_case(str[j]) == 1)
                return(printf("bash: syntax error near unexpected token `<>'\n"), 0);
        }
        if(operator(str[j]) == 3 || operator(str[j]) == 1 || operator(str[j]) == 7 || operator(str[j]) == 6)
        {
            num_puts = count_puts(str[j]);
            // printf("num : %d\n", num_puts);
            if (num_puts == -3)
                return(printf("bash: syntax error near unexpected token `<'\n"), 0);
            if (num_puts < -3)
                return(printf("bash: syntax error near unexpected token `<<'\n"), 0);
            if (num_puts == 3)
                return(printf("bash: syntax error near unexpected token `>'\n"), 0);
            if (num_puts > 3)
                return(printf("bash: syntax error near unexpected token `>>'\n"), 0);
        }
        if((operator(str[j]) == 1 || operator(str[j]) == 3 || operator(str[j]) == 6 || operator(str[j]) == 7))
        {
            if (all_space(str[j + 1]) == 1)
                j++;
            if((operator(str[j + 1]) == 1 || operator(str[j + 1]) == 3 || operator(str[j + 1]) == 6 || operator(str[j + 1]) == 7))
            {
                num_puts = count_puts_two(str[j + 1]);
                if (num_puts == -1)
                    return(printf("bash: syntax error near unexpected token `<'\n"), 0);
                if (num_puts <= -2)
                    return(printf("bash: syntax error near unexpected token `<<'\n"), 0);
                if (num_puts == 1)
                    return(printf("bash: syntax error near unexpected token `>'\n"), 0);
                if (num_puts >= 2)
                    return(printf("bash: syntax error near unexpected token `>>'\n"), 0);
            }
        }
        j++;
    }
    return(1);
}


int check_files_puts(char** str)
{
    int j;
    int num_puts;

    j = 0;
    num_puts = 0;
    while(str[j])
    {
        
        
        if((operator(str[j]) == 1 || operator(str[j]) == 3 || operator(str[j]) == 6 || operator(str[j]) == 7) && !str[j + 1])
            return(printf("bash: syntax error near unexpected token `newline'\n"), 0);

        j++;
    }
    return(1);
}

int check_pipe(char** split, char** ope, int i, int j)
{
    int num_pipes;

    num_pipes = 0;
    if (i == 0)
    {
        if (split[j - 1] == NULL)
        {
            num_pipes = count_pipes(ope[i]);
            if(num_pipes == 2)
                return(printf("bash: syntax error near unexpected token `|'\n"), 0);
            if(num_pipes > 2)
                return(printf("bash: syntax error near unexpected token `||'\n"), 0);
            return(1);
        }
            
    }
    num_pipes = count_pipes(ope[i]) - 1;
    if(num_pipes == 1)
        return(printf("bash: syntax error near unexpected token `|'\n"), 0);
    if(num_pipes > 1)
        return(printf("bash: syntax error near unexpected token `||'\n"), 0);
    return(1);
}

int check_puts(char** split, char** ope, int i, int j)
{
    int num_puts;

    num_puts = 0;
    num_puts = count_puts(ope[i]);
    if (num_puts == -3)
        return(printf("bash: syntax error near unexpected token `<'\n"), 0);
    if (num_puts < -3)
        return(printf("bash: syntax error near unexpected token `<<'\n"), 0);
    if (num_puts == 3)
        return(printf("bash: syntax error near unexpected token `>'\n"), 0);
    if (num_puts > 3)
        return(printf("bash: syntax error near unexpected token `>>'\n"), 0);
    if(ope[i + 1] == NULL)
    {
        if(split[j + 1] == NULL)
        {
            return(printf("bash: syntax error near unexpected token `newline'\n"), 0);
        }
        j++;
        while (all_space(split[j]) == 1 && split[j])
            j++;
        if(operator(split[j]) == 5 || operator(split[j]) == 8)
        {
            num_puts = count_pipes(split[j]);
            if(num_puts == 1)
                return(printf("bash: syntax error near unexpected token `|'\n"), 0);
            if(num_puts > 1)
                return(printf("bash: syntax error near unexpected token `||'\n"), 0);
        }
        
        if(operator(split[j]) == 6 || operator(split[j]) == 7 || operator(split[j]) == 1 || operator(split[j]) == 3)
        {
            num_puts = count_puts_two(split[j]);
            if (num_puts == -1)
                return(printf("bash: syntax error near unexpected token `<'\n"), 0);
            if (num_puts <= -2)
                return(printf("bash: syntax error near unexpected token `<<'\n"), 0);
            if (num_puts == 1)
                return(printf("bash: syntax error near unexpected token `>'\n"), 0);
            if (num_puts >= 2)
                return(printf("bash: syntax error near unexpected token `>>'\n"), 0);
        }
        return(1);
    }
    if(operator(ope[i + 1]) == 5 || operator(ope[i + 1]) == 8 )
    {
        num_puts = count_pipes(ope[i + 1]);
        if(num_puts == 1)
            return(printf("bash: syntax error near unexpected token `|'\n"), 0);
        if(num_puts > 1)
            return(printf("bash: syntax error near unexpected token `||'\n"), 0);
    }
    else
    {
        num_puts = count_puts_two(ope[i + 1]);
        if (num_puts == -1)
            return(printf("bash: syntax error near unexpected token `<'\n"), 0);
        if (num_puts <= -2)
            return(printf("bash: syntax error near unexpected token `<<'\n"), 0);
        if (num_puts == 1)
            return(printf("bash: syntax error near unexpected token `>'\n"), 0);
        if (num_puts >= 2)
            return(printf("bash: syntax error near unexpected token `>>'\n"), 0);
    }
        
}

int check_operator(char** split)
{
    int j;
    int i;
    char** ope;
    int check;

    j = 0;
    check = 1;
     j= 0;
    while (split[j])
    {
        if(operator(split[j]) != 0)
        {
            ope = ft_split_ope(split[j]);
            i = 0;
            while(ope[i])
            {
                if (operator(ope[i]) == 2)
                    check = check_pipe(split, ope, i, j);
                if (operator(ope[i]) == 8)
                    return(printf("bash: syntax error near unexpected token `&'\n"), 0);
                if (operator(ope[i]) == 6 || operator(ope[i]) == 7 || operator(ope[i]) == 1 || operator(ope[i]) == 3)
                    check = check_puts(split, ope, i, j);
                if (check == 0)
                    return(0);
                i++;
            }
        }
        j++;
    }
    return(1);
}

t_list *creat_list(char* line, char **envp, char **argv, int argc)
{
    int count;
    char** content_node;
    t_list *command;
    int i = 0;


    if (all_space(line) == 1)
        return(NULL);
    count = count_node(line);
    //printf("||||count||||%d\n\n", count); // print_info
    content_node = ft_split_txt(line);
    if (check_operator(content_node) == 0)
       return(NULL);
    command = init_list(count, envp, argv, argc);
    fill_ope_list(command, content_node);
    fill_com_list(command, content_node);
    fill_file_list(command, content_node);
    if(check_pipes(content_node, command) == 0)
        return(NULL);
    del_space(command);
    // printf("delim |%s| \n\n", command->delim); // print_info
    del_quotes(command);
    command->data->content = content_node;
    // print_list(command); // print_info
    //fill_list(&command, content_node);
    return (command);
}
