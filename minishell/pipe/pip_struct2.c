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
int ft_strrchr(const char *string, int searchedChar)
{
	int		i;
	int		check;
	int	result;

	i = 0;
	check = 0;
	while (string[i] != '\0')
	{
		if (string[i] == (unsigned char)searchedChar)
		{
			result = i;
			check++;
		}
		i++;
	}
	if (string[i] == (unsigned char)searchedChar)
	{
		result = i;
		check++;
	}
	if (check != 0)
		return (result);
	return (0);
}


char*	recup_path(char *src)
{
	unsigned int	i;
	unsigned int	n;
	int size;
	char* dst;

	size = ft_strrchr(src, '/');
	i = 0;
	n = size;
	if (size == 0)
		return (NULL);
	dst = malloc(size + 2);
	while (i < n && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

void type1(t_list *pip)
{
    int		fd_out;
	char* path;

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
	// ft_printf_fd(2, "fd: %d, file: |%s|", fd_out, pip->if_file2);
	// if (is_other(pip) != 1 || pip->data->n_cmd != 1)
		dup2(fd_out, STDOUT_FILENO); 
	close(fd_out);
}

void type1bis(t_list *pip)
{
    int		fd_out;

    if (access(pip->if_file2, F_OK) == 0 && access(pip->if_file2, W_OK) == -1)
	{
		ft_printf_fd(2, "bash: permission denied: %s\n", pip->if_file2);
		(free_pip(pip), exit(EXIT_FAILURE));
	}
    fd_out = open(pip->if_file2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	// ft_printf_fd(2, "fd: %d, file: |%s|", fd_out, pip->if_file2);
	// if (is_other(pip) != 1 || pip->data->n_cmd != 1)
	dup2(fd_out, STDOUT_FILENO); 
	close(fd_out);
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
