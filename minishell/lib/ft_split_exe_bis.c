/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_exe_bis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lismarti <lismarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 10:19:13 by lismarti          #+#    #+#             */
/*   Updated: 2025/03/08 10:36:02 by lismarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	istokenquotes(char *s, int start_s)
{
	char	*temp;
	char	afterquotes;

	if (s[start_s] != '\'' && s[start_s] != '\"')
		return (0);
	temp = ft_strchr(s + start_s + 1, s[start_s]);
	if (!temp || !temp[0])
		return (0);
	afterquotes = temp[1];
	if (isin(" \0\t", afterquotes) == 1 || temp[1] == '\0')
		return (1);
	else
		return (0);
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

int	if_quote(char *s, int start_s, char c, int i)
{
	char	q;

	while (s[i] && s[i] != '\'' && s[i] != '\"' && s[i] != c && s[i] != '\t')
		i++;
	if (s[i] == '\'' || s[i] == '\"')
	{
		q = s[i++];
		while (s[i] != q && s[i])
			i++;
		if (s[i])
			i++;
	}
	return (i);
}
