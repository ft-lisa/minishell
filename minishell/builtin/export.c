/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lismarti <lismarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:35:23 by lismarti          #+#    #+#             */
/*   Updated: 2025/03/13 15:36:55 by lismarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*update_existing_2(char ***env, char *key, char *comb, int i)
{
	char	*entry;

	entry = malloc(ft_strlen(key) + 1 + ft_strlen(comb) + 1);
	if (!entry)
		return (free(comb), NULL);
	ft_strcpy(entry, key);
	ft_strcat(entry, "=");
	ft_strcat(entry, comb);
	free(comb);
	free((*env)[i]);
	(*env)[i] = entry;
}

static int	update_existing(char ***env, char *key, char *new_val)
{
	int		i;
	size_t	klen;
	char	*old;
	char	*comb;
	char	*entry;

	klen = ft_strlen(key);
	i = 0;
	while ((*env)[i])
	{
		if (strncmp((*env)[i], key, klen) == 0 && (*env)[i][klen] == '=')
		{
			old = (*env)[i] + klen + 1;
			comb = malloc(ft_strlen(old) + ft_strlen(new_val) + 1);
			if (!comb)
				return (-1);
			ft_strcpy(comb, old);
			ft_strcat(comb, new_val);
			entry = update_existing_2(env, key, comb, i);
			if (!entry)
				return (-1);
			return (1);
		}
		i++;
	}
}

int	add_plus(char ***env, char *add)
{
	char	*key;
	char	*new_val;
	int		ret;
	char	*entry;

	key = extract_key(add);
	if (!key)
		return (0);
	new_val = add + (ft_strlen(key) + 2);
	ret = update_existing(env, key, new_val);
	if (ret == 1)
		return (free(key), 1);
	if (ret == -1)
		return (free(key), 0);
	entry = malloc(strlen(key) + 1 + strlen(new_val) + 1);
	if (!entry)
		return (free(key), 0);
	ft_strcpy(entry, key);
	ft_strcat(entry, "=");
	ft_strcat(entry, new_val);
	free(key);
	if (add_last_2d(env, entry) != 0)
		return (free(entry), 0);
	return (free(entry), 1);
}

void	export2(t_list *pip, char **str, int i)
{
	char	*temp;

	temp = parcing_export(str[i], 0);
	if (export_valid(str[i]) == 2)
		add_plus(pip->data->envp, temp);
	else if (export_valid(str[i]) == 1)
		add_last_2d(pip->data->envp, temp);
	else if (export_valid(str[i]) == 0)
	{
		ft_printf_fd(2, "bash: export: ʻ%s': not a valid identifier\n", str[i]);
		pip->data->new_exit = 1;
	}
	else if (export_valid(str[i]) == 3)
	{
		ft_printf_fd(2, "bash: export: %c%c: invalid option\n", str[i][0],
			str[i][1]);
		pip->data->new_exit = 2;
	}
	if (temp)
		free(temp);
}

void	export1(t_list *pip, char **str)
{
	int	i;

	i = 1;
	if (!str[1])
		while ((*(pip->data->envp))[i])
			ft_printf_fd(1, "%s\n", (*(pip->data->envp))[i++]);
	else
	{
		while (str[i])
		{
			export2(pip, str, i);
			i++;
		}
	}
}
