/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lismarti <lismarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:55:17 by lismarti          #+#    #+#             */
/*   Updated: 2025/03/13 17:17:12 by lismarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*remove_surrounding_quotes(const char *s)
{
	size_t	len;
	char	*res;

	len = strlen(s);
	if (len >= 2 && ((s[0] == '\"' && s[len - 1] == '\"') || (s[0] == '\''
				&& s[len - 1] == '\'')))
	{
		res = malloc(len - 1);
		if (!res)
			return (NULL);
		ft_memcpy(res, s + 1, len - 2);
		res[len - 2] = '\0';
		return (res);
	}
	res = strdup(s);
	return (res);
}

char	*m_process_backslashes(const char *s)
{
	size_t	i;
	size_t	j;
	char	*res;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == '\\' && s[i + 1])
		{
			i += 2;
			j++;
		}
		else
		{
			i++;
			j++;
		}
	}
	res = malloc(j + 1);
	return (res);
}
