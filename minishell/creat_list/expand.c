/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lismarti <lismarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:29:39 by lismarti          #+#    #+#             */
/*   Updated: 2025/03/13 15:31:42 by lismarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	indexto_skip_squotes(char *str, char c, int i, int in_double)
{
	while (str[(i > 0) * (i - 1)] && str[i])
	{
		if (str[i] == '"')
		{
			in_double = !in_double;
			i++;
			continue ;
		}
		if (!in_double && str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
			continue ;
		}
		if (isdollar_alone(str, i) == 1)
		{
			i++;
			continue ;
		}
		if (str[i++] == c)
			return (i - 1);
	}
	return (-1);
}

int	expand_special_case(char **cmd, int error, int i)
{
	char	*temp;

	temp = ft_itoa(error);
	if (!temp)
		return (-1);
	replace_str(cmd, "?", temp, i);
	free(temp);
	return (0);
}

int	expand_variable(char **cmd, char **env, char *var, int i)
{
	char	*value;

	if (isin_2d_equal(env, var))
	{
		value = get_path_var(env, var);
		replace_str(cmd, var, value, i);
	}
	else
		replace_str(cmd, var, NULL, i);
	free(var);
	return (0);
}

int	expand(char **cmd, char **env, int error)
{
	char	*var;
	int		i;

	i = indexto_skip_squotes(*cmd, '$', 0, 0);
	if (i == -1 || (*cmd)[i] == '\0')
		return (1);
	var = copy_until_alnum_under(*cmd + i + 1);
	if (!var)
		return (-1);
	if (ft_strncmp(var, "?", 1) == 0)
		return (free(var), expand_special_case(cmd, error, i));
	return (expand_variable(cmd, env, var, i));
}

int	expand_vars(char **cmd, char ***env, int error)
{
	int		check;
	int		j;
	char	*str;

	check = 0;
	j = 0;
	str = ft_strdup(*cmd);
	if (!str)
		return (-1);
	while (check == 0)
	{
		check = expand(&str, *env, error);
	}
	*cmd = str;
	if (isemptyor_spacetab(*cmd) == 1)
	{
		free(*cmd);
		check = -1;
	}
	return (check);
}
