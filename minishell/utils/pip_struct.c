#include "../minishell.h"

void	free_pip(t_pipex *pip)
{
	ft_close_all(pip->fd);
	cleanexit_int(pip->fd);
	cleanexit(pip->path);
	free(pip->pid);
	free(pip);
}

char	**get_path(char *envp[])
{
	int		i;
	int		j;
	char	*p1;
	char	**path1;

	i = 0;
	p1 = "PATH=";
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] == p1[j])
			j++;
		if (j == 5)
		{
			path1 = ft_split_exe(envp[i] + j, ':');
			return (path1);
		}
		i++;
	}
	return (NULL);
}

int	**ft_add_fd(int **fd, int len)
{
	int	**new_fd;
	int	i;

	i = 0;
	new_fd = malloc((len + 2) * sizeof(int *));
	if (!new_fd)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_fd[i] = fd[i];
		i++;
	}
	new_fd[i++] = malloc(2 * sizeof(int));
	if (len == 0)
	{
		new_fd[0][0] = -1;
		new_fd[0][1] = -1;
	}
	new_fd[i] = NULL;
	return (free(fd), new_fd);
}

t_list	*init_pipex(t_list *pipex, char **envp, char **argv, int argc)
{
	pipex = malloc(sizeof(t_pipex));
	if (!pipex)
		return (NULL);
	pipex->envp = envp;
	pipex->v = argv;
	pipex->fd = NULL;
	pipex->fd = ft_add_fd(pipex->fd, 0);
	if (!pipex->fd)
	{
		free(pipex);
		return (NULL);
	}
	pipex->path = NULL;
	pipex->pid = malloc((argc) * sizeof(int));
	if (!pipex->pid)
		return (free(pipex), NULL);
	pipex->path = ft_split_exe("error env", ' ');
	if (pipex->envp[0] && pipex->envp[0][0] != 'V')
	{
		cleanexit(pipex->path);
		pipex->path = get_path(pipex->envp);
	}
	return (pipex);
}

int	wait_all(int *pid, int len)
{
	int	i;
	int	k;
	int	rn;

	i = 0;
	k = 0;
	rn = 0;
	while (i < len)
	{
		waitpid(pid[i], &k, 0);
		i++;
	}
	rn = k >> 8;
	return (rn);
}
