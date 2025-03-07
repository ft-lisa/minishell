/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_ope_bis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lismarti <lismarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:35:37 by smendez-          #+#    #+#             */
/*   Updated: 2025/03/07 11:51:17 by lismarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	splitlen4(char const *s1, char c1)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (s1[i])
	{
		while (s1[i] == c1 && s1[i])
		{
			if (s1[i] == '"' || s1[i] == '\'')
				i = pass_quote_plus(s1[i], s1, i + 1);
			i++;
		}
		if (s1[i])
			k++;
		while (s1[i] != c1 && s1[i])
		{
			if (s1[i] == '"' || s1[i] == '\'')
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
		if (s[i] == '"' || s[i] == '\'')
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

int	split2(char const *s, int i)
{
	if (s[i] == '"' || s[i] == '\'')
		i = pass_quote_plus(s[i], s, i + 1);
	i++;
	return (i);
}

char	**ft_split_ope_bis(char const *s, char c, int i, int j)
{
	char	**t1;

	t1 = malloc((splitlen4(s, c) + 1) * sizeof(char *));
	if (t1 == NULL)
		return (NULL);
	while (s[i])
	{
		while (s[i] == c && s[i])
			i = split2(s, i);
		if (!s[i])
			break ;
		t1[j] = t2f(s, i, c);
		if (t1[j++] == NULL)
			return (NULL);
		while (s[i] != c && s[i])
		{
			if (s[i] == '"' || s[i] == '\'')
				i = pass_quote_plus(s[i], s, i + 1);
			i++;
		}
	}
	t1[j] = NULL;
	j = 0;
	return (t1);
}
