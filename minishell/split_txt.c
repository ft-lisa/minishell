/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_txt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lismarti <lismarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:14:14 by lismarti          #+#    #+#             */
/*   Updated: 2025/02/05 17:21:08 by lismarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		while ((s1[i] == '|' || s1[i] == '<' || s1[i] == '>') && s1[i])
			i++;
		if (s1[i])
			k++;
		while ((s1[i] != '|' && s1[i] != '<' && s1[i] != '>') && s1[i])
			i++;
	}
	return (k);
}

static char	**cleanexit(char **a)
{
	int	i;

	i = 0;
	while (a[i])
	{
		free(a[i]);
		i++;
	}
	free(a);
	return (NULL);
}

static char	*t2f(char const *s, int start_s)
{
	int		i;
	int		len_s;
	char	*t2;

	i = start_s;
	while ((s[i] == '|' || s[i] == '<' || s[i] == '>') && s[i])
		i++;
	if (i == start_s)
	{
		while ((s[i] != '|' && s[i] != '<' && s[i] != '>') && s[i])
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
			return (cleanexit(t1));
		check = i;
		while ((s[i] != '|' && s[i] != '<' && s[i] != '>') && s[i])
			i++;
		if (i == check)
		{
			while ((s[i] == '|' || s[i] == '<' || s[i] == '>') && s[i])
				i++;
		}
	}
	return (t1[j] = NULL, t1);
}

// int	main(int argc, char **argv)
// {
// 	char	**toto;
// 	int		i;

// 	toto = ft_split(argv[1]);
// 	while (toto[i] != NULL)
// 	{
// 		printf("%s\n", toto[i]);
// 		i++;
// 	}
// }
