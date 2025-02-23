/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smendez- <smendez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 11:57:04 by smendez-          #+#    #+#             */
/*   Updated: 2025/02/17 17:04:07 by smendez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

// int	main(int argc, char *argv[], char *envp[])
// {
// 	t_list	*pip;
// 	t_list	*head;
// 	int		i;

// 	i = 1;
// 	// printf("THIS IS: %s\n\n\\n", argv[1]); // print_info
// 	pip = creat_list(argv[1], envp, argv, argc);
// 	head = pip;
// 	// printf("N cmds: %d \n\n", pip->data->n_cmd); // print_info
// 	pip->data->pid[0] = fork();
// 	if (pip->data->pid[0] == 0)
// 		(exe_isolate(pip, pip->exe1, pip->exe2));
// 	while(i < pip->data->n_cmd)
// 	{
// 		pip = pip->next;
// 		waitpid(pip->data->pid[pip->index - 2], NULL, 0);
// 		pip->data->pid[i] = fork();
// 		if (pip->data->pid[i] == 0)
// 			(exe_isolate(pip, pip->exe1, pip->exe2));
// 		i++;
// 	}
//         ft_close_all(pip->data->fd);
// 	i = wait_all(pip->data->pid, pip->data->n_cmd);
// 	return (free_pip(head), i);
// }
