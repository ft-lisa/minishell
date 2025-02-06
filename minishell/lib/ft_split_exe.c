/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_exe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smendez- <smendez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:35:37 by smendez-          #+#    #+#             */
/*   Updated: 2025/02/06 11:48:49 by smendez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	no_space_until_q(char const *s, int start_s, char c)
{
	while (s[start_s] != '\'')
	{
		if (s[start_s] == c || s[start_s] == '\0')
			return (0);
		start_s++;
	}
	return (1);
}

int	if_next_quote(char const *s, int start_s, char c, int i)
{
	if (s[start_s] == '\'')
	{
		i = start_s + 1;
		while (s[i] != '\'' && s[i])
			i++;
		if (s[i])
			return (i + 1);
	}
	else if (no_space_until_q(s, start_s, c) == 1)
	{
		while (s[i] != '\'' && s[i])
			i++;
		i++;
		while (s[i] != '\'' && s[i])
			i++;
		if (s[i])
			return (i + 1);
	}
	else
	{
		while (s[i] != c && s[i])
			i++;
	}
	return (i);
}

static char	*t2f(char const *s, int start_s, char c)
{
	int		i;
	int		len_s;
	char	*t2;

	i = start_s;
	i = if_next_quote(s, start_s, c, i);
	if (s[start_s] == '\'')
	{
		start_s++;
		i--;
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

int	splitlen(char const *s1, char c1)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (s1[i])
	{
		while (s1[i] == c1 && s1[i])
			i++;
		if (s1[i])
			k++;
		while (s1[i] != c1 && s1[i])
			i++;
	}
	return (k);
}

char	**ft_split_exe(char *s, char c)
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
			i++;
		if (!s[i])
			break ;
		t1[j] = t2f(s, i, c);
		if (t1[j++] == NULL)
			return (cleanexit(t1));
		i = if_next_quote(s, i, c, i);
	}
	t1[j] = NULL;
	return (t1);
}

// int	main(int c, char *v[])
// {
// 	int		i;
// 	int		j;
// 	char	**a;

// 	(void)c;
// 	i = 0;
// 	a = ft_split(v[1], v[2][0]);
// 	while (a[i])
// 	{
// 		printf("%s\n", a[i]);
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
