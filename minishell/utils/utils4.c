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
