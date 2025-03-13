/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_list_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lismarti <lismarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:33:30 by lismarti          #+#    #+#             */
/*   Updated: 2025/03/13 15:33:36 by lismarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_line(char **line, char ***envp, int error)
{
	add_history(*line);
	if (all_space(*line) == 1)
		return (1);
	if (open_only_one_quote(*line) == 1)
		return (1);
	if (check_operator(*line) == 1)
		return (2);
	if (expand_vars(line, envp, error) == -1)
		return (1);
	if (isemptyor_spacetab(*line) == 1)
		return (1);
	return (0);
}

char	**prepare_content_node(char *line, char ***envp)
{
	char	**content_node;

	content_node = ft_split_ope_bis(line, '|', 0, 0);
	free(line);
	if (!content_node)
		(cleanexit(*envp), free(envp), exit(1));
	return (content_node);
}

void	trim_content_node(char **content_node)
{
	int		i;
	char	*temp;

	i = 0;
	while (content_node[i])
	{
		temp = content_node[i];
		content_node[i] = ft_strtrim(content_node[i], " ");
		free(temp);
		i++;
	}
}

int	fill_command_data(t_list *command, char **content_node)
{
	if (fill_ope_list(command, content_node) == -1)
		return (free_list(command), -1);
	if (fill_com_list(command, content_node) == -1)
		return (free_list(command), -1);
	return (0);
}
