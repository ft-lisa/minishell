/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lismarti <lismarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:34:56 by lismarti          #+#    #+#             */
/*   Updated: 2025/03/13 17:01:10 by lismarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**allocate_new_array(int nitems)
{
	char	**t;

	t = malloc(nitems * sizeof(char *));
	if (!t)
		return (NULL);
	return (t);
}

int	copy_non_matching_items(char **src, char **dest, char *rmv)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = 0;
	while (src[j])
	{
		temp = copy_until(src[j], '=');
		if (!temp)
			return (cleanexit(dest), 1);
		if (ft_strcmp(temp, rmv) != 0)
		{
			dest[i] = ft_strdup(src[j]);
			if (!dest[i++])
				return (cleanexit(dest), 1);
		}
		free(temp);
		j++;
	}
	dest[i] = NULL;
	return (0);
}

int	rmv_str_2d(char ***str2, char *rmv)
{
	char	**t;
	int		nitems;

	if (!rmv || isin_2d_delim(*str2, rmv, '=') == 0)
		return (0);
	nitems = str_len_2d(*str2);
	t = allocate_new_array(nitems);
	if (!t)
		return (1);
	if (copy_non_matching_items(*str2, t, rmv) == 1)
		return (1);
	cleanexit(*str2);
	*str2 = t;
	return (0);
}

int	unset_valid(char *str)
{
	int	r;

	if (str[0] >= '0' && str[0] <= '9')
		return (0);
	if (str[0] == '-' && str[1])
		return (3);
	r = ft_isalnum_under_plus(str);
	if (r == 2)
		return (0);
	return (r);
}

int	unset1(t_list *pip, char **str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (unset_valid(str[i]) == 1)
			rmv_str_2d(pip->data->envp, str[i]);
		else if (unset_valid(str[i]) == 0)
		{
			ft_printf_fd(2, "bash: unset: ʻ%s': not a valid identifier\n",
				str[i]);
			pip->data->new_exit = 1;
		}
		else if (unset_valid(str[i]) == 3)
		{
			ft_printf_fd(2, "bash: unset: %c%c: invalid option\n", str[i][0],
				str[i][1]);
			pip->data->new_exit = 2;
		}
		i++;
	}
}
