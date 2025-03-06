/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_txt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lismarti <lismarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:14:14 by lismarti          #+#    #+#             */
/*   Updated: 2025/03/06 14:49:39 by lismarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	splitlen6(char const *s1)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (s1[i] != '\0')
	{
		if (s1[i] == '|' || s1[i] == '<' || s1[i] == '>' || s1[i] == '&')
			k++;
		while ((s1[i] == '|' || s1[i] == '<' || s1[i] == '>' || s1[i] == '&')
			&& s1[i] != '\0')
		{
			if (s1[i] == '"' || s1[i] == '\'')
				i = pass_quote_plus(s1[i], s1, i + 1);
			i++;
		}
		if (s1[i])
			k++;
		while ((s1[i] != '|' && s1[i] != '<' && s1[i] != '>' && s1[i] != '&')
			&& s1[i] != '\0')
		{
			if (s1[i] == '"' || s1[i] == '\'')
				i = pass_quote_plus(s1[i], s1, i + 1);
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

	i = start_s;
	while ((s[i] == '|' || s[i] == '<' || s[i] == '>' || s[i] == '&') && s[i])
	{
		if (s[i] == '"' || s[i] == '\'')
			i = pass_quote_plus(s[i], s, i + 1);
		i++;
	}
	if (i == start_s)
	{
		while ((s[i] != '|' && s[i] != '<' && s[i] != '>' && s[i] != '&')
			&& s[i])
		{
			if (s[i] == '"' || s[i] == '\'')
				i = pass_quote_plus(s[i], s, i + 1);
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

char	**ft_split_txt(char const *s)
{
	char	**t1;
	int		i;
	int		j;
	int		check;

	t1 = malloc((splitlen6(s) + 1) * sizeof(char *));
	if (t1 == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		t1[j] = t2f(s, i);
		if (t1[j++] == NULL)
			return (NULL);
		check = i;
		while ((s[i] != '|' && s[i] != '<' && s[i] != '>' && s[i] != '&')
			&& s[i])
		{
			if (s[i] == '"' || s[i] == '\'')
				i = pass_quote_plus(s[i], s, i + 1);
			i++;
		}
		if (i == check)
		{
			while ((s[i] == '|' || s[i] == '<' || s[i] == '>' || s[i] == '&')
				&& s[i])
			{
				if (s[i] == '"' || s[i] == '\'')
					i = pass_quote_plus(s[i], s, i + 1);
				i++;
			}
		}
	}
	return (t1[j] = NULL, t1);
}
