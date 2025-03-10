/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_mini.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lismarti <lismarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:35:37 by smendez-          #+#    #+#             */
/*   Updated: 2025/03/10 14:20:46 by lismarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	next_token(char *s, int start_s, char c, int i)
{
	char	quote;
	int		isquote;

	isquote = 0;
	while (s[start_s])
	{
		if (isin("\'\"", s[start_s]) == 1 && isquote == 0)
		{
			isquote = 1;
			quote = s[start_s++];
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

char	*ft_malloc(int len_s)
{
	char	*t2;

	t2 = malloc((len_s + 1) * sizeof(char));
	if (t2 == NULL)
		return (NULL);
	return (t2);
}

static char	*t3f(char *s, int *start_s, char c, int i)
{
	int		len_s;
	int		inside;
	char	*t2;

	len_s = next_token(s, *start_s, c, *start_s) - *start_s;
	inside = 0;
	t2 = ft_malloc(len_s);
	if (!t2)
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

int	splitlen2(char *s1)
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

	t1 = malloc((splitlen2(s) + 1) * sizeof(char *));
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
		t1[j] = t3f(s, &i, 'a', 0);
		if (t1[j++] == NULL)
			return (cleanexit(t1));
		while (s[i] && s[i] != ' ' && s[i] != '\t')
			i++;
	}
	t1[j] = NULL;
	return (t1);
}
