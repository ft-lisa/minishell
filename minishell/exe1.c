/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smendez- <smendez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 11:57:04 by smendez-          #+#    #+#             */
/*   Updated: 2025/02/10 16:57:48 by smendez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

char	*get_path_command(char **paths, char *command)
{
	int		i;
	int		j;
	char	*temp;
	char	*temp2;
	char	*path;

	i = 0;
	j = -1;
	if ((command == NULL) | (paths[0] == NULL))
		return (ft_calloc(1, 1));
	while (j != 0 && paths[i])
	{
		temp = ft_strjoin(paths[i++], "/");
		temp2 = ft_strjoin(temp, command);
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

void type7(t_list *pip)
{
	int *mini_pipe;
	int stdout1;

	mini_pipe = malloc(sizeof(int *) * 2);
	if (!mini_pipe)
		return;
	if (pipe(mini_pipe) == -1)
			perror("minipipe");
	stdout1 = dup(STDOUT_FILENO);
	if (stdout1 == -1)
		(perror("dup minipipe"), exit(EXIT_FAILURE));
	if (dup2(mini_pipe[1], STDOUT_FILENO) == -1)
		(perror("dup2 minipipe"), exit(EXIT_FAILURE));
	ft_until_limiter(pip->delim);	
	if (dup2(mini_pipe[0], STDIN_FILENO) == -1)
                (perror("dup2 minipipe"), exit(EXIT_FAILURE));
	if (dup2(stdout1, STDOUT_FILENO) == -1)
                (perror("dup2 minipipe"), exit(EXIT_FAILURE));
	close(mini_pipe[0]);
	close(mini_pipe[1]);
	free(mini_pipe);
}

void type6(t_list *pip)
{
        int		open_fd;

	if (access(pip->if_file1, F_OK) == -1)
        {
                ft_printf_fd(2, "bash: %s: No such file or directory\n", pip->if_file1);
                (free_pip(pip), exit(EXIT_FAILURE));
        }
        if (access(pip->if_file1, R_OK) == -1)
        {
                ft_printf_fd(2, "bash: permission denied: %s\n", pip->if_file1);
                (free_pip(pip), exit(EXIT_FAILURE));
        }
        open_fd = open(pip->if_file1, O_RDONLY);
        if (dup2(open_fd, STDIN_FILENO) == -1)
                (perror("dup2"), exit(EXIT_FAILURE));
        close(open_fd);
}

void type5(t_list *pip)
{
	// ft_printf_fd(2, "cmd1: fd: %d\n\n", pip->index - 2); // print_info
	if (dup2(pip->data->fd[pip->index - 2][0], STDIN_FILENO) == -1)
		(perror("dup2 2"), exit(EXIT_FAILURE));
}

void type1(t_list *pip)
{
        int		fd_out;

        if (access(pip->if_file2, F_OK) == 0 && access(pip->if_file2, W_OK) == -1)
	{
		ft_printf_fd(2, "bash: permission denied: %s\n", pip->if_file2);
		(free_pip(pip), exit(EXIT_FAILURE));
	}
        fd_out = open(pip->if_file2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	ft_printf_fd(2, "fd: %d, file: |%s|", fd_out, pip->if_file2 );
	(dup2(fd_out, STDOUT_FILENO), close(fd_out));
}

void type2(t_list *pip)
{
	// ft_printf_fd(2, "cmd1: fd: %d\n\n", pip->index - 1); // print_info
        if (dup2(pip->data->fd[pip->index - 1][1], STDOUT_FILENO) == -1)
		(perror("dup2 1"), exit(EXIT_FAILURE));
}

void type3(t_list *pip)
{
        int		fd_out;
	
        if (access(pip->if_file2, F_OK) == 0 && access(pip->if_file2, W_OK) == -1)
	{
		ft_printf_fd(2, "bash: permission denied: %s\n", pip->if_file2);
		(free_pip(pip), exit(EXIT_FAILURE));
	}
        fd_out = open(pip->if_file2, O_APPEND | O_WRONLY | O_CREAT, 0644);
	(dup2(fd_out, STDOUT_FILENO), close(fd_out));
}


void	exe_isolate(t_list *pip, int t1, int t2)
{
	char	**temp2;
	char	*no_a;
	char	*get_p;

	if (t1 == 5) 
                type5(pip);
        else if (t1 == 6) 
                type6(pip);
        else if (t1 == 7)
                type7(pip);
        if (t2 == 1)
                type1(pip);
	else if (t2 == 2)
                type2(pip);
	else if (t2 == 3)
                type3(pip);
	ft_close_all(pip->data->fd);
	temp2 = ft_split_exe(pip->cmd, ' ');
	no_a = no_args_cmd(pip->cmd);
	get_p = get_path_command(pip->data->path, no_a);
	execve(get_p, temp2, pip->data->envp);
	ft_printf_fd(2, "%s: command not found\n", temp2[0]);
	(cleanexit(temp2), free_pip(pip), free(no_a), free(get_p), exit(127));
}

int exe1(int argc, char *argv[], char *envp[])
{
	t_list	*pip;
	t_list	*head;
	int		i;

	i = 1;
	// printf("THIS IS: %s\n\n\\n", argv[1]); // print_info
	pip = creat_list(argv[1], envp, argv, argc);
	head = pip;
	// printf("N cmds: %d \n\n", pip->data->n_cmd); // print_info
	pip->data->pid[0] = fork();
	if (pip->data->pid[0] == 0)
		(exe_isolate(pip, pip->exe1, pip->exe2));
	while(i < pip->data->n_cmd)
	{
		pip = pip->next;
		waitpid(pip->data->pid[pip->index - 2], NULL, 0);
		pip->data->pid[i] = fork();
		if (pip->data->pid[i] == 0)
			(exe_isolate(pip, pip->exe1, pip->exe2));
		i++;
	}
        ft_close_all(pip->data->fd);
	i = wait_all(pip->data->pid, pip->data->n_cmd);
	return (free_pip(head), i);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_list	*pip;
	t_list	*head;
	int		i;

	i = 1;
	// printf("THIS IS: %s\n\n\\n", argv[1]); // print_info
	pip = creat_list(argv[1], envp, argv, argc);
	head = pip;
	// printf("N cmds: %d \n\n", pip->data->n_cmd); // print_info
	pip->data->pid[0] = fork();
	if (pip->data->pid[0] == 0)
		(exe_isolate(pip, pip->exe1, pip->exe2));
	while(i < pip->data->n_cmd)
	{
		pip = pip->next;
		waitpid(pip->data->pid[pip->index - 2], NULL, 0);
		pip->data->pid[i] = fork();
		if (pip->data->pid[i] == 0)
			(exe_isolate(pip, pip->exe1, pip->exe2));
		i++;
	}
        ft_close_all(pip->data->fd);
	i = wait_all(pip->data->pid, pip->data->n_cmd);
	return (free_pip(head), i);
}
