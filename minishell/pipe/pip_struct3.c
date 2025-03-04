#include "../minishell.h"

void type7(t_list *pip)
{
	int mini_pipe[2];
	int i;

	i = 0;
	if (pipe(mini_pipe) == -1)
	{
		perror("minipipe");
		return;
	}
	while (pip->delim[i + 1])
	{
		ft_until_limiter(pip->delim[i++], 0, mini_pipe);
		if(sig_g == 2)
		{
			ft_close_all(pip->data->fd);
			exit(130) ;
		}		
	}	
	ft_until_limiter(pip->delim[i], 1, mini_pipe);
	if(sig_g == 2)
	{
		ft_close_all(pip->data->fd);
		exit(130) ;
	}
	close(mini_pipe[1]);
	if (dup2(mini_pipe[0], STDIN_FILENO) == -1)
	{
		perror("dup2 minipipe");
		exit(EXIT_FAILURE);
	}
	close(mini_pipe[0]);
	if (!pip->cmd)
	{
		free_pip(pip);
		exit(0);
	}
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

void	exe_build_single(t_list *pip, int t1, int t2)
{
	char	**temp2;
	char	*no_a;
	char	*get_p;
	struct stat st;

	if (is_other(pip) == 1)
        ;
	else if (t1 == 5) 
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
	if (is_other(pip) == 1)
		exe_other(pip);
}

void	exe_isolate(t_list *pip, int t1, int t2)
{
	char	**temp2;
	char	*no_a;
	char	*get_p;
	struct stat st;

	if (is_other(pip) == 1)
        ;
	else if (t1 == 5) 
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
	if (is_other(pip) == 1)
		exe_other(pip);
	temp2 = ft_split_exe1(pip->cmd);
	no_a = no_args_cmd(temp2[0]);
	get_p = get_path_command(pip->data->path, no_a);
	if ((!get_p || !get_p[0]) && pip->data->path)
	{
		ft_printf_fd(2, "bash: %s: command not found\n", temp2[0]);
		(cleanexit(temp2), free_pip(pip), free(no_a), free(get_p), exit(127));
	}
	//print_split(temp2);
	execve(get_p, temp2, *(pip->data->envp));
	if (stat(get_p, &st) == 0 && S_ISDIR(st.st_mode))
		ft_printf_fd(2, "bash: %s: Is a directory\n", no_a);
	else
		ft_printf_fd(2, "bashh: %s: %s\n", no_a, strerror(errno));
	if (errno == 2)
		errno = 127;
	else if (errno == 13)
		errno = 126;
	(cleanexit(temp2), free_pip(pip), free(no_a), free(get_p), exit(errno));
}

int exe1(t_list *pip)
{
	t_list	*head;
	int		i;

	i = 1;
	head = pip;
	if (is_other(pip) == 1 && pip->data->n_cmd == 1 && pip->exe1 != 7)
    {
		exe_other(pip);
		// exe_build_single(pip, pip->exe1, pip->exe2);
	}
	else
	{
		if (pip->exe1 == 7)
			signal(SIGINT, parent_her);
		pip->data->pid[0] = fork();
		if (pip->data->pid[0] == 0)
			(exe_isolate(pip, pip->exe1, pip->exe2));
	}
	while(i < pip->data->n_cmd)
	{
		pip = pip->next;
		// waitpid(pip->data->pid[pip->index - 2], NULL, 0);
		pip->data->pid[i] = fork();
		if (pip->data->pid[i] == 0)
			(exe_isolate(pip, pip->exe1, pip->exe2));
		i++;
	}
    ft_close_all(pip->data->fd);
	i = wait_all(pip->data->pid, pip->data->n_cmd, pip);
	return (free_pip(head), i);
}
