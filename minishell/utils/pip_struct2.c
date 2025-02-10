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
