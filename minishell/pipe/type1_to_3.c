#include "../minishell.h"

void	type1(t_list *pip)
{
	int		fd_out;
	char	*path;

	if (isin(pip->if_file2, '/') == 1)
	{
		path = recup_path(pip->if_file2);
		if (access(path, F_OK) == -1)
		{
			write(2, "bash: ", 6);
			write(2, pip->if_file2, strlen(pip->if_file2));
			write(2, ": No such file or directory\n", 28);
			(free(path), free_pip(pip), exit(EXIT_FAILURE));
		}
		free(path);
	}
	if (access(pip->if_file2, F_OK) == 0 && access(pip->if_file2, W_OK) == -1)
	{
		ft_printf_fd(2, "bash: permission denied: %s\n", pip->if_file2);
		(free_pip(pip), exit(EXIT_FAILURE));
	}
	fd_out = open(pip->if_file2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
}

void	type1bis(t_list *pip)
{
	int	fd_out;

	if (access(pip->if_file2, F_OK) == 0 && access(pip->if_file2, W_OK) == -1)
	{
		ft_printf_fd(2, "bash: permission denied: %s\n", pip->if_file2);
		(free_pip(pip), exit(EXIT_FAILURE));
	}
	fd_out = open(pip->if_file2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
}

void	type2(t_list *pip)
{
	if (dup2(pip->data->fd[pip->index - 1][1], STDOUT_FILENO) == -1)
		(perror("dup2 1"), exit(EXIT_FAILURE));
}

void	type3(t_list *pip)
{
	int	fd_out;

	if (access(pip->if_file2, F_OK) == 0 && access(pip->if_file2, W_OK) == -1)
	{
		ft_printf_fd(2, "bash: permission denied: %s\n", pip->if_file2);
		(free_pip(pip), exit(EXIT_FAILURE));
	}
	fd_out = open(pip->if_file2, O_APPEND | O_WRONLY | O_CREAT, 0644);
	(dup2(fd_out, STDOUT_FILENO), close(fd_out));
}