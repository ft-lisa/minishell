#include "../minishell.h"

static int	splitlen(char const *s1)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (s1[i])
	{
        if (s1[i] == '|')
        {
            k++;
            while (s1[i] == '|' && s1)
                i++;
        }
        if (s1[i] == '&')
        {
            k++;
            while (s1[i] == '&' && s1)
                i++;
        }
        if (s1[i] == '<' || s1[i] == '>')
        {
            k++;
            while ((s1[i] == '<' || s1[i] == '>') && s1)
                i++;
        }
	}
	return (k);
}

static char	*t2f(char const *s, int start_s)
{
	int		i;
	int		len_s;
	char	*t2;
    char    lettre;

	i = start_s;
    lettre = s[start_s];
    if (lettre == '<' || lettre == '>')
    {
        while ((s[i] == '<' || s[i] == '>') && s[i])
        {
            i++;	
        }
    }
    else
    {
        while (s[i] == lettre && s[i])
        {
            i++;			
        }
    }		
	len_s = i - start_s;
	i = 0;
	t2 = malloc((len_s + 1) * sizeof(char));
	if (t2 == NULL)
		return (NULL);
	while (i < len_s)
	{
		t2[i] = s[start_s + i];
		i++;
	}
	t2[i] = '\0';
	return (t2);
}

char	**ft_split_ope(char const *s)
{
	char	**t1;
	int		i;
	int		j;
	char lettre;

	t1 = malloc((splitlen(s) + 1) * sizeof(char *));
	if (t1 == NULL)
		return (NULL);
	i = 0;
	j = 0;
	//printf("taille %d\n",splitlen(s));
	while (s[i])
	{
		t1[j] = t2f(s, i);
		if (t1[j++] == NULL)
			return (NULL);//cleanexit(t1)
        lettre = s[i];
        if (lettre == '<' || lettre == '>')
        {
            while ((s[i] == '<' || s[i] == '>') && s[i])
            {
                i++;	
            }
        }
        else
        {
            while (s[i] == lettre && s[i])
            {
                i++;	
            }
	    }
    }
		
	return (t1[j] = NULL, t1);
}

#include <stdio.h>

int	main(int c, char *v[])
{
	int		i;
	char	**a;

	(void)c;
	i = 0;
	a = ft_split_ope(v[1]);
	while (a[i])
	{
		printf("%s\n", a[i]);
		i++;
	}
	i = 0;
	return (0);
}