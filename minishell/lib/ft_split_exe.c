/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_exe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smendez- <smendez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:35:37 by smendez-          #+#    #+#             */
/*   Updated: 2025/03/04 14:07:31 by smendez-         ###   ########.fr       */
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

int	istokenquotes(char *s, int start_s)
{
	char	*temp;
	char	afterquotes;

	// ft_printf_fd(2, "content: s|%s| s[s]|%s|\n", s, s + start_s);
	if (s[start_s] != '\'' && s[start_s] != '\"')
		return (0);
	temp = ft_strchr(s + start_s + 1, s[start_s]);
	// ft_printf_fd(2, "content: temp|%s|\n", temp);
	if (!temp || !temp[0])
		return (0);
	afterquotes = temp[1];
	if (isin(" \0\t", afterquotes) == 1 || temp[1] == '\0')
		return (1);
	else return (0);
}

int	no_space_until_q(char *s, int start_s, char c)
{
	while (s[start_s] != '\'' && s[start_s] != '\"')
	{
		if (s[start_s] == c || s[start_s] == '\t' || s[start_s] == '\0')
			return (0);
		start_s++;
	}
	return (1);
}

int	if_next_quote(char *s, int start_s, char c, int i)
{
	// ft_printf_fd(2, "NEXT QUOTE: content: s|%s| s[s]|%s|\n", s, s + start_s);
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

		while (s[i] && s[i] != '\'' && s[i] != '\"' && s[i] != c && s[i] != '\t')
			i++;
		if (s[i] == '\'' || s[i] == '\"')
		{
			char q = s[i];
			i++;
			while (s[i] != q && s[i])
				i++;
			if (s[i])
				i++;
		}
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
	int	count_quotes;

	if (inside == 1)
		return (i - start_s);
	temp1 = copy_until_one(s + start_s, " \t");
	count_quotes = (count_c(temp1, '\'') + (count_c(temp1, '\"')));
	free(temp1);	
	return (i - start_s - count_quotes);
}

static char	*t2f(char *s, int start_s, char c, int start)
{
	int		i;
	int		len_s;
	int		inside;
	char	*t2;

	i = start_s;
	i = if_next_quote(s, start_s, c, i);
	inside = 0;
	if (s[start_s] == '\'' || s[start_s] == '\"')
	{
		start_s++;
		i--;
		inside++;
	}
	len_s = i - start_s;
	// ft_printf_fd(2, "len |%d| i |%d| inside |%d|\n\n", len_s, i, inside);
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
// 	a = ft_split_exe(v[1], v[2][0]);
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
