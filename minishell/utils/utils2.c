/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lismarti <lismarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:51:05 by lismarti          #+#    #+#             */
/*   Updated: 2025/03/13 17:28:42 by lismarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*del_c(char *str, char c)
{
	int		i;
	int		k;
	char	*new_s;

	i = 0;
	k = 0;
	if (!str || str == NULL)
		return (NULL);
	while (str[i])
		if (str[i++] != c)
			k++;
	new_s = malloc((k + 1) * sizeof(char));
	if (!new_s)
		return (NULL);
	k = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != c)
			new_s[k++] = str[i];
		i++;
	}
	new_s[k] = '\0';
	free(str);
	return (new_s);
}

char	*get_path_command(char **paths, char *command, int i, int j)
{
	char	*temp;
	char	*temp2;
	char	*path;

	if (isin(command, '/') == 1)
		return (ft_strdup(command));
	if ((command == NULL) || (paths == NULL))
		return (ft_calloc(1, 1));
	while (j != 0 && paths[i])
	{
		temp = ft_strjoin(paths[i++], "/");
		if (!temp)
			return (NULL);
		temp2 = ft_strjoin(temp, command);
		if (!temp2)
			return (NULL);
		j = access(temp2, F_OK);
		if (j == 0)
			path = ft_strdup(temp2);
		free(temp);
		free(temp2);
	}
	if (j == 0)
		return (path);
	return (ft_calloc(1, 1));
}

char	*no_args_cmd(char *cmd)
{
	int		i;
	int		j;
	char	*first_cmd;

	i = 0;
	j = 0;
	if (cmd == NULL)
		return (ft_strdup("Error"));
	while (cmd[i] && cmd[i] != ' ')
		i++;
	if (ft_strlen(cmd) == (size_t)i)
		return (ft_strdup(cmd));
	first_cmd = malloc((i + 1) * sizeof(char));
	if (!first_cmd)
		return (NULL);
	while (j < i)
	{
		first_cmd[j] = cmd[j];
		j++;
	}
	first_cmd[j] = '\0';
	return (first_cmd);
}

int	operator(char *txt)
{
	int	i;

	i = 0;
	if (txt == NULL)
		return (-1);
	if (txt[i] == '|')
		return (2);
	if (txt[i] == '>' && txt[i + 1] == '>')
		return (3);
	if (txt[i] == '>')
		return (1);
	if (txt[i] == '<' && txt[i + 1] == '<')
		return (7);
	if (txt[i] == '<')
		return (6);
	if (txt[i] == '&')
		return (8);
	return (0);
}
