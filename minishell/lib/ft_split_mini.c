/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_mini.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smendez- <smendez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:35:37 by smendez-          #+#    #+#             */
/*   Updated: 2025/03/04 14:02:40 by smendez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int	count_c(char *str, char c)
// {
// 	int	i;
// 	int	count;

// 	i = 0;
// 	count = 0;
// 	if (!str || !str[0] || !c)
// 		return (0);
// 	while(str[i])
// 	{
// 		if (str[i] == c)
// 			count++;
// 		i++;
// 	}
// 	return (count);
// }

// int	isin(char *s, char c)
// {
// 	int	i;

// 	i = 0;
// 	while (s[i])
// 	{
// 		if (s[i] == c)
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

// char	**cleanexit(char **a)
// {
// 	int	i;

// 	i = 0;
// 	while (a[i])
// 	{
// 		free(a[i]);
// 		i++;
// 	}
// 	free(a);
// 	return (NULL);
// }

int	next_token(char *s, int start_s, char c)
{
	char	quote;
	int	isquote;
	int	i;

	i = start_s;
	isquote = 0;
	while(s[start_s])
	{
		if (isin("\'\"", s[start_s]) == 1 && isquote == 0)
		{
			isquote = 1;
			quote = s[start_s];
			start_s++;
		}
		if (isquote == 1 && s[start_s] == quote)
		{
			isquote = 0;
			start_s++;
			continue ;
		}
		if (!s[start_s])
			return (i);
		if (isin(" \t", s[start_s]) == 1 && isquote == 0)
			return (i);
		i++;
		start_s++;
	}
	return (i);
}


static char	*t2f(char *s, int *start_s, char c, int start)
{
	int		i;
	int		len_s;
	int		inside;
	char	*t2;

	i = next_token(s, *start_s, c);
	len_s = i - *start_s;
	i = 0;
	inside = 0;
	t2 = malloc((len_s + 1) * sizeof(char));
	if (t2 == NULL)
		return (NULL);
	while (i < len_s)
	{
		if (isin("\'\"", s[*start_s]) == 1 && inside == 0)
		{
			inside = 1;
			c = s[(*start_s)++];
		}
		if (inside == 1 && s[*start_s] == c)
		{
			inside = 0;
			(*start_s)++;
			continue ;
		}
		t2[i++] = s[*start_s];
		(*start_s)++;
	}
	t2[i] = '\0';
	return (t2);
}

int	splitlen1(char *s1)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (s1[i])
	{
		while (s1[i] && (s1[i] == ' ' || s1[i] == '\t'))
			i++;
		if (s1[i])
			k++;
		while (s1[i] && s1[i] != ' ' && s1[i] != '\t')
			i++;
	}
	return (k);
}

char	**ft_split_exe1(char *s)
{
	char	**t1;
	int		i;
	int		j;

	t1 = malloc((splitlen1(s) + 1) * sizeof(char *));
	if (t1 == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && (s[i] == ' ' || s[i] == '\t'))
			i++;
		if (!s[i])
			break ;	
		t1[j] = t2f(s, &i, 'a', i);
		if (t1[j++] == NULL)
			return (cleanexit(t1));
		while (s[i] && s[i] != ' ' && s[i] != '\t')
			i++;
	}
	// ft_printf_fd(2, "split size |%d| split used |%d|\n", (splitlen1(s, c) + 1), j );
	t1[j] = NULL;
	// print_split(t1);
	return (t1);
}

// int	main(int c, char *v[])
// {
// 	int		i;
// 	int		j;
// 	char	**a;

// 	(void)c;
// 	i = 0;
// 	a = ft_split_exe1(v[1]);
// 	while (a[i])
// 	{
// 		printf("|%s|\n", a[i]);
// 		// j = 0;
// 		// while(a[i][j])
// 		// {
// 		// 	printf("printing char index |%d| as |%c|\n", j, a[i][j]);
// 		// 	j++;
// 		// }
// 		i++;
// 	}
// 	i = 0;
// 	while (a[i])
// 	{
// 		free(a[i]);
// 		i++;
// 	}
// 	free(a);
// 	printf("\n%s\n", v[1]);
// 	return (0);
// }

// int	main(int c, char *v[])
// {
// 	printf("\n%s\n", v[1]);
// 	return (0);
// }
