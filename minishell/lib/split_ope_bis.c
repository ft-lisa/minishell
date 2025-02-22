/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_ope_bis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lismarti <lismarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:35:37 by smendez-          #+#    #+#             */
/*   Updated: 2025/02/22 10:40:07 by lismarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"



// echo dfasg       sdfdsf "|dfadfa     ''  |" dsfdsf


static int	splitlen(char const *s1, char c1)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (s1[i])
	{
		while (s1[i] == c1 && s1[i])
		{
			if(s1[i] == '"' || s1[i] == '\'')
				i = pass_quote_plus(s1[i], s1, i + 1);
			i++;						
		}
		if (s1[i])
			k++;
		while (s1[i] != c1 && s1[i])
		{
			if(s1[i] == '"' || s1[i] == '\'')
				i = pass_quote_plus(s1[i], s1, i + 1);
			i++;	
		}
	}
	return (k);
}

static char	*t2f(char const *s, int start_s, char c)
{
	int		i;
	int		len_s;
	char	*t2;

	i = start_s;
	while (s[i] != c && s[i])
	{
		if(s[i] == '"' || s[i] == '\'')
			i = pass_quote_plus(s[i], s, i + 1);	
		i++;			
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

char	**ft_split_ope_bis(char const *s, char c)
{
	char	**t1;
	int		i;
	int		j;

	t1 = malloc((splitlen(s, c) + 1) * sizeof(char *));
	if (t1 == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
		{
			if(s[i] == '"' || s[i] == '\'')
				i = pass_quote_plus(s[i], s, i + 1);	
			i++;	
		}
		if (!s[i])
			break ;
		t1[j] = t2f(s, i, c);
		if (t1[j++] == NULL)
			return (NULL); //cleanexit(t1)
		while (s[i] != c && s[i])
		{
			if(s[i] == '"' || s[i] == '\'')
				i = pass_quote_plus(s[i], s, i + 1);	
			i++;	
		}
	}
	t1[j] = NULL;
    j = 0;
    //del(t1);
	return (t1);
}

// #include <stdio.h>

// int	main(int c, char *v[])
// {
// 	int		i;
// 	char	**a;

// 	(void)c;
// 	i = 0;
// 	a = ft_split_ope_bis(v[1], v[2][0]);
// 	while (a[i])
// 	{
// 		printf("|%s|\n", a[i]);
// 		i++;
// 	}
// 	i = 0;
// 	return (0);
// }
