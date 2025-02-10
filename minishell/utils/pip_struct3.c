#include "../minishell.h"

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

int exe1(t_list *pip)
{
	t_list	*head;
	int		i;

	i = 1;
	head = pip;
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
