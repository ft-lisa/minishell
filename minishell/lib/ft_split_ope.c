/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_ope.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lismarti <lismarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:26:16 by lismarti          #+#    #+#             */
/*   Updated: 2025/03/06 14:36:07 by lismarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	splitlen2(char const *s1)
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
			while ((s1[i] == '|' || s1[i] == ' ' || s1[i] == 9) && s1)
				i++;
		}
		if (s1[i] == '<' || s1[i] == '>')
		{
			k++;
			while ((s1[i] == '<' || s1[i] == '>' || s1[i] == ' ' || s1[i] == 9)
				&& s1)
				i++;
		}
	}
	return (k);
}

void	ft_copy(int start_s, int len_s, char const *s, char *t2)
{
	int	i;

	i = 0;
	while (i < len_s)
	{
		if (s[start_s + i] != ' ' && s[start_s + i] != 9)
			t2[i] = s[start_s + i];
		else
			start_s++;
		i++;
	}
}

static char	*t2f(char const *s, int start_s)
{
	int		i;
	int		len_s;
	char	*t2;
	char	lettre;
	int		space;

	i = start_s;
	space = 0;
	lettre = s[start_s];
	if (lettre == '<' || lettre == '>')
		while ((s[i] == '<' || s[i] == '>' || s[i] == ' ' || s[i] == 9) && s[i])
			if (s[i++] == ' ')
				space++;
	else
		while (s[i] == lettre && s[i])
			if (s[i++] == ' ')
				space++;
	len_s = i - start_s - space;
	i = 0;
	t2 = malloc((len_s + 1) * sizeof(char));
	if (t2 == NULL)
		return (NULL);
	ft_copy(start_s, len_s, s, t2);
	t2[i] = '\0';
	return (t2);
}

char	**ft_split_ope(char const *s)
{
	char	**t1;
	int		i;
	int		j;
	char	lettre;

	t1 = malloc((splitlen2(s) + 1) * sizeof(char *));
	if (t1 == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		t1[j] = t2f(s, i);
		if (t1[j++] == NULL)
			return (NULL);
		lettre = s[i];
		if (lettre == '<' || lettre == '>')
			while ((s[i] == '<' || s[i] == '>' || s[i] == ' ' || s[i] == 9)
				&& s[i])
				i++;
		else
			while ((s[i] == lettre || s[i] == ' ' || s[i] == 9) && s[i])
				i++;
	}
	return (t1[j] = NULL, t1);
}
