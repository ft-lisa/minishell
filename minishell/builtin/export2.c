/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lismarti <lismarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:54:58 by lismarti          #+#    #+#             */
/*   Updated: 2025/03/13 17:17:29 by lismarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*process_backslashes(const char *s)
{
	size_t	i;
	size_t	j;
	char	*res;

	i = 0;
	j = 0;
	res = m_process_backslashes(s);
	if (!res)
		return (NULL);
	while (s[i])
	{
		if (s[i] == '\\' && s[i + 1])
		{
			res[j++] = s[i + 1];
			i += 2;
		}
		else
			res[j++] = s[i++];
	}
	res[j] = '\0';
	return (res);
}

char	*parcing_export_2(char *value, char *key, char *res)
{
	char	*tmp;

	tmp = process_backslashes(value);
	free(value);
	if (!tmp)
		return (free(key), NULL);
	res = malloc(ft_strlen(key) + ft_strlen(tmp) + 2);
	if (!res)
		return (free(key), free(tmp), NULL);
	ft_strcpy(res, key);
	ft_strcat(res, "=");
	ft_strcat(res, tmp);
	free(key);
	free(tmp);
	return (res);
}

char	*parcing_export(char *str, size_t key_len)
{
	char	*eq;
	char	*key;
	char	*value;
	char	*tmp;
	char	*res;

	eq = ft_strchr(str, '=');
	if (!eq)
		return (ft_strdup(str));
	key_len = (size_t)(eq - str);
	key = malloc(key_len + 1);
	if (!key)
		return (NULL);
	ft_strncpy(key, str, key_len);
	key[key_len] = '\0';
	value = remove_surrounding_quotes(eq + 1);
	if (!value)
		return (free(key), NULL);
	return (parcing_export_2(value, key, res));
}

int	export_valid(char *str)
{
	char	**temp;
	int		r;

	if (str[0] >= '0' && str[0] <= '9')
		return (0);
	if (str[0] == '-' && str[1])
		return (3);
	temp = ft_split(str, '=');
	if (!temp)
		return (-1);
	r = ft_isalnum_under_plus(temp[0]);
	cleanexit(temp);
	return (r);
}

char	*extract_key(char *s)
{
	char	*p;
	char	*key;
	size_t	len;

	p = ft_strstr(s, "+=");
	if (!p)
		return (NULL);
	len = p - s;
	key = malloc(len + 1);
	if (!key)
		return (NULL);
	ft_strncpy(key, s, len);
	key[len] = '\0';
	return (key);
}
