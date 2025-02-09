/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_txt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lismarti <lismarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:14:14 by lismarti          #+#    #+#             */
/*   Updated: 2025/02/07 14:30:16 by lismarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int pass_quote(char quote, const char* str, int i)
{
    while(str[i] != quote && str[i] != '\0')
        i++;
	i++;
	while(str[i] == ' ')
		i++;
    return(i);
}

static int	splitlen(char const *s1)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (s1[i])
	{
		if (s1[i] == '|' || s1[i] == '<' || s1[i] == '>')
			k++;
		while ((s1[i] == '|' || s1[i] == '<' || s1[i] == '>') && s1[i] != '"' && s1[i] != '\'' && s1[i])
			i++;
		if (s1[i])
			k++;
		if(s1[i] == '"' || s1[i] == '\'')
				i = pass_quote(s1[i], s1, i + 1);
		while ((s1[i] != '|' && s1[i] != '<' && s1[i] != '>') && s1[i] != '"' && s1[i] != '\'' && s1[i])
			i++;
		if(s1[i] == '"' || s1[i] == '\'')
				i = pass_quote(s1[i], s1, i + 1);
	}
	return (k);
}

static char	*t2f(char const *s, int start_s)
{
	int		i;
	int		len_s;
	char	*t2;

	i = start_s;
	while ((s[i] == '|' || s[i] == '<' || s[i] == '>') && s[i] != '"' && s[i] != '\'' && s[i])
		i++;
	if(s[i] == '"' || s[i] == '\'')
				i = pass_quote(s[i], s, i + 1);
	if (i == start_s)
	{
		while ((s[i] != '|' && s[i] != '<' && s[i] != '>') && s[i] != '"' && s[i] != '\''&& s[i])
			i++;
		if(s[i] == '"' || s[i] == '\'')
				i = pass_quote(s[i], s, i + 1);
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

char	**ft_split_txt(char const *s)
{
	char	**t1;
	int		i;
	int		j;
	int		check;

	t1 = malloc((splitlen(s) + 1) * sizeof(char *));
	if (t1 == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		t1[j] = t2f(s, i);
		if (t1[j++] == NULL)
			return (NULL);//cleanexit(t1)
		check = i;
		while ((s[i] != '|' && s[i] != '<' && s[i] != '>') && s[i] != '"' && s[i] != '\''&& s[i])
			i++;
		if(s[i] == '"' || s[i] == '\'')
				i = pass_quote(s[i], s, i + 1);
		if (i == check)
		{
			while ((s[i] == '|' || s[i] == '<' || s[i] == '>') && s[i] != '"' && s[i] != '\'' && s[i])
				i++;
			if(s[i] == '"' || s[i] == '\'')
				i = pass_quote(s[i], s, i + 1);
		}
	}
	return (t1[j] = NULL, t1);
}

// int	main(int c, char *v[])
// {
// 	int		i;
// 	char	**a;

// 	(void)c;
// 	i = 0;
// 	a = ft_split_txt(v[1]);
// 	while (a[i])
// 	{
// 		printf("%s\n", a[i]);
// 		i++;
// 	}
// 	i = 0;
// 	return (0);
// }
