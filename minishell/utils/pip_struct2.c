#include "../minishell.h"

void	ft_close_all(int **fd)
{
	int	i;
	int	j;

	i = 0;
	if (fd[0][0] < 0)
		return;
	while (fd[i])
	{
		j = 0;
		while (j < 2)
		{
			close(fd[i][j++]);
		}
		i++;
	}
}
