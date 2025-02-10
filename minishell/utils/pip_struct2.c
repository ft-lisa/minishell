#include "../minishell.h"

void	ft_close_all(int **fd)
{
	int	i;
	int	j;

	i = 0;
	if (!fd || !fd[0])
		return;
	while (fd[i])
	{
		j = 0;
		while (j < 2)
		{
			if(fd[i][j] != -1)
				close(fd[i][j]);
			j++;
		}
		i++;
	}
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
