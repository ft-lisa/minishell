/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lismarti <lismarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:01:02 by lismarti          #+#    #+#             */
/*   Updated: 2025/03/13 11:13:53 by lismarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
void init_list2(t_list *list)
{
        list->cmd = NULL;
        list->index = -1;
        list->exe1 = -1;
        list->exe2 = -1;
        list->if_file1 = NULL;
        list->if_file2 = NULL;
        list->delim = NULL;
}

int	no_env_init(char ***envp)
{
	char	*temp;
	char	*path;
	
	path = pwd2((t_list *)"");
	if (path)
	{
		temp = ft_strjoin("PWD=", path);
        if (!temp)
            return(free(path), -1);
		add_last_2d(envp, temp);
		free(temp);
		free(path);
	}
	add_last_2d(envp, "SHLVL=1");
	add_last_2d(envp, "_=/usr/bin/env");
}


t_list *create_new_node(t_list *first, t_data *data)
{
	t_list *new_node;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return (free_list(first), NULL);
	new_node->data = data;
	return (new_node);
}

t_list *init_list(int count, char ***envp, char **argv)
{
	t_list *first;
	t_list *list;
	t_data *data;

	first = malloc(sizeof(t_list));
	if (!first)
		return (NULL);
	data = init_exe(envp, argv, count);
	if (!data)
		return (free(first), NULL);
	first->data = data;
	list = first;
	while (count--)
	{
		init_list2(list);
		if (count > 0)
		{
			list->next = create_new_node(first, data);
			if (!list->next)
				return (NULL);
			list = list->next;
		}
	}
	list->next = NULL;
	return (first);
}

int     check_line(char **line, char ***envp, int error)
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

char **prepare_content_node(char *line, char ***envp)
{
	char **content_node;

	content_node = ft_split_ope_bis(line, '|', 0, 0);
	free(line);
	if (!content_node)
		(cleanexit(*envp), free(envp), exit(1));
	return (content_node);
}

void trim_content_node(char **content_node)
{
	int i;
	char *temp;

	i = 0;
	while (content_node[i])
	{
		temp = content_node[i];
		content_node[i] = ft_strtrim(content_node[i], " ");
		free(temp);
		i++;
	}
}

int fill_command_data(t_list *command, char **content_node)
{
	if (fill_ope_list(command, content_node) == -1)
		return (free_list(command), -1);
	if (fill_com_list(command, content_node) == -1)
		return (free_list(command), -1);
	return (0);
}

t_list *create_list(char *line, char ***envp, char **argv)
{
	char **content_node;
	t_list *command;
	int count;

	content_node = prepare_content_node(line, envp);
	if (!content_node)
		return (NULL);
	count = double_strlen(content_node);
	command = init_list(count, envp, argv);
	if (!command)
		return (NULL);
	trim_content_node(content_node);
	if (fill_command_data(command, content_node) == -1)
		return (NULL);
	del_space(command);
	del_quotes(command);
	command->data->content = content_node;
	return (command);
}
