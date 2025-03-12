/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pip_struct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lismarti <lismarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:10:16 by lismarti          #+#    #+#             */
/*   Updated: 2025/03/12 16:53:47 by lismarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_pip(t_list *pip)
{
	if (!pip)
		return ;
	// ft_printf_fd(2, "errno3 |%d| \n\n", errno);
	if (errno != 126 && errno != 127)
		ft_close_all(pip->data->fd);
	// ft_printf_fd(2, "errno4 |%d| \n\n", errno);
	cleanexit_int(pip->data->fd);
	if (pip->data->path)
		cleanexit(pip->data->path);
	cleanexit(pip->data->content);
	free(pip->data->pid);
	free(pip->data);
	free_list(pip);
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
	new_fd[i] = malloc(2 * sizeof(int));
	if (!new_fd[i])
		return (NULL);
	new_fd[i][0] = -1;
	new_fd[i][1] = -1;
	new_fd[i + 1] = NULL;
	if (fd)
		free(fd);
	return (new_fd);
}



t_data	*init_exe2(t_data *pipex, char ***envp, char **argv, int count)
{
	pipex = malloc(sizeof(t_data));
	if (!pipex)
		return(NULL);
	if (str_len_2d(*envp) < 6)
		no_env_init(envp);
	pipex->envp = envp;
	pipex->v = argv;
	pipex->fd = ft_add_fd(NULL, 0);
	if (!pipex->fd)
		(free(pipex), exit(1));
	pipex->n_cmd = count;
	pipex->path = NULL;
	return (pipex);
	pipex->exit1 = 0;
	pipex->new_exit = 0;
}

t_data	*init_exe(char ***envp, char **argv, int count)
{
	t_data	*pipex;
	int		i;

	i = 1;
	pipex = init_exe2(pipex, envp, argv, count);
	if (!pipex)
		return(NULL);
	// while (i < pipex->n_cmd)
	// {
	// 	pipex->fd = ft_add_fd(pipex->fd, i);
	// 	if (pipe(pipex->fd[i - 1]) == -1)
	// 		perror("pipe1");
	// 	i++;
	// }
	pipex->pid = malloc(count * sizeof(int));
	if (!pipex->pid)
		return (free(pipex), NULL);
	pipex->pid[0] = 0;
	pipex->path = ft_split("error env", ' ');
	if (!pipex->path)
		exit(1);
	if (pipex->envp[0][0])
		if (*(pipex->envp)[0][0] != 'V')
			(cleanexit(pipex->path), pipex->path = get_path(*(pipex->envp)));
	return (pipex);
}
