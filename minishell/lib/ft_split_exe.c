/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_exe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lismarti <lismarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:35:37 by smendez-          #+#    #+#             */
/*   Updated: 2025/03/10 14:56:38 by lismarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	if_next_quote(char *s, int start_s, char c, int i)
{
	if (s[start_s] == '\'' || s[start_s] == '\"')
	{
		i = start_s + 1;
		while (s[i] && s[i] != s[start_s])
			i++;
		if (s[i])
			return (i + 1);
	}
	else if (no_space_until_q(s, start_s, c) == 1)
	{
		i = if_quote(s, start_s, c, i);
		while (s[i] && s[i] != c && s[i] != '\t')
			i++;
		return (i);
	}
	else
	{
		while (s[i] && s[i] != c && s[i] != '\t')
			i++;
	}
	return (i);
}

int	len_t2f(int i, int start_s, int inside, char *s)
{
	char	*temp1;
	int		count_quotes;

	if (inside == 1)
		return (i - start_s);
	temp1 = copy_until_one(s + start_s, " \t");
	if (!temp1)
		return (-1);
	count_quotes = (count_c(temp1, '\'') + (count_c(temp1, '\"')));
	free(temp1);
	return (i - start_s - count_quotes);
}

static char	*t2f(char *s, int start_s, char c, int start)
{
	int			i;
	int			len_s;
	static int	inside = 0;
	char		*t2;

	i = if_next_quote(s, start_s, c, start_s);
	if (s[start_s] == '\'' || s[start_s] == '\"')
	{
		start_s++;
		i--;
		inside++;
	}
	len_s = i - start_s;
	i = 0;
	t2 = malloc((len_s + 1) * sizeof(char));
	if (t2 == NULL)
		return (NULL);
	while (i < len_s)
	{
		if (inside == 1 || isin("\'\"", s[start_s]) == 0)
			t2[i++] = s[start_s];
		start_s++;
	}
	t2[i] = '\0';
	return (t2);
}

int	splitlen1(char *s1, char c1)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (s1[i])
	{
		while (s1[i] && (s1[i] == c1 || s1[i] == '\t'))
			i++;
		if (s1[i])
			k++;
		while (s1[i] && s1[i] != c1 && s1[i] != '\t')
			i++;
	}
	return (k);
}

char	**ft_split_exe(char *s, char c)
{
	char	**t1;
	int		i;
	int		j;

	t1 = malloc((splitlen1(s, c) + 5) * sizeof(char *));
	if (t1 == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && (s[i] == c || s[i] == '\t'))
			i++;
		if (!s[i])
			break ;
		t1[j] = t2f(s, i, c, i);
		if (t1[j++] == NULL)
			return (cleanexit(t1));
		i = if_next_quote(s, i, c, i);
	}
	t1[j] = NULL;
	return (t1);
}
