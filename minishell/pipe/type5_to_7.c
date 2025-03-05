#include "../minishell.h"

// void	quit_sigint(t_list* pip)
// {
// 	if (g_sig == 2)
// 	{
// 		ft_close_all(pip->data->fd);
// 		exit(130);
// 	}
// }

// void	type7(t_list *pip)
// {
// 	int	mini_pipe[2];
// 	int	i;

// 	i = 0;
// 	if (pipe(mini_pipe) == -1)
// 	{
// 		perror("minipipe");
// 		return ;
// 	}
// 	while (pip->delim[i + 1])
// 	{
// 		ft_until_limiter(pip->delim[i++], 0, mini_pipe);
// 		quit_sigint(pip);
// 	}
// 	ft_until_limiter(pip->delim[i], 1, mini_pipe);
// 	quit_sigint(pip);
// 	close(mini_pipe[1]);
// 	if (dup2(mini_pipe[0], STDIN_FILENO) == -1)
// 	{
// 		perror("dup2 minipipe");
// 		exit(EXIT_FAILURE);
// 	}
// 	close(mini_pipe[0]);
// 	if (!pip->cmd)
// 		(free_pip(pip), exit(0));
// }

// void	type6(t_list *pip)
// {
// 	int	open_fd;

// 	if (access(pip->if_file1, F_OK) == -1)
// 	{
// 		ft_printf_fd(2, "bash: %s: No such file or directory\n", pip->if_file1);
// 		(free_pip(pip), exit(EXIT_FAILURE));
// 	}
// 	if (access(pip->if_file1, R_OK) == -1)
// 	{
// 		ft_printf_fd(2, "bash: permission denied: %s\n", pip->if_file1);
// 		(free_pip(pip), exit(EXIT_FAILURE));
// 	}
// 	open_fd = open(pip->if_file1, O_RDONLY);
// 	if (dup2(open_fd, STDIN_FILENO) == -1)
// 		(perror("dup2"), exit(EXIT_FAILURE));
// 	close(open_fd);
// }

// void	type5(t_list *pip)
// {
// 	if (dup2(pip->data->fd[pip->index - 2][0], STDIN_FILENO) == -1)
// 		(perror("dup2 2"), exit(EXIT_FAILURE));
// }