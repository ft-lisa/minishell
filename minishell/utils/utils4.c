# include "../minishell.h"

size_t	ft_strlen(const char *c)
{
	size_t	i;

	i = 0;
	while (c[i] != '\0')
		i++;
	return (i);
}
int pass_quote_plus(char quote, const char* str, int i)
{
	int j;

	j = i;
	while(str[i] != quote && str[i] != '\0')
	i++;
	if (str[i] == '\0')
	return(j);
	return(i);
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

int	wait_all(int *pid, int len, t_list *pip)
{
	int	i;
	int	k;
	int	rn;

	i = 0;
	k = 0;
	rn = 0;
	if (is_other(pip) == 1 && pip->data->n_cmd == 1)
		return (pip->data->new_exit);
	if (!pid || !pid[0])
		return (0);
	while (i < len)
	{
		waitpid(pid[i], &k, 0);
		i++;
	}
	rn = k >> 8;
	return (rn);
}
