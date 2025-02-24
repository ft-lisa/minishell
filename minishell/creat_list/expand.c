#include "../minishell.h"

int	replace_str(char **mainstr, char *before, char *after, int index)
{
	char	*new;
	int	i;
	int	len_a;
	int	len_b;

	i = 0;
	len_a = 0;
	if (after)
		len_a = ft_strlen(after);
	if (before == NULL)
		return (-1);
	len_b = ft_strlen(before);
	new = malloc ((ft_strlen((*mainstr)) - len_b + len_a  + 1) * sizeof(char));
	while(i < index)
	{
		new[i] = (*mainstr)[i];
		i++;
	}
	i = 0;
	while(after[i])
	{
		new[index + i] = after[i];
		i++;
	}
	while((*mainstr)[index + len_b])
	{
		new[index + len_a] = (*mainstr)[index + len_b];
		index++;
	}
	new[index + len_a] = '\0';
	free(*mainstr);
	*mainstr = new;
	return (0);
}

int	expand(char *cmd, char ***env)
{
	char	*new;
	char	*temp;
	char	*temp2;
	int	i;

	i = 0;
	while (cmd[i] && cmd[i] != '$')
		i++;
	temp = copy_until_one(cmd + i + 1, "<>|$\"");
	if (isin_2d_equal((*env), temp) == 1)
	{
		
	}
}

int 	expand_vars(char **cmd, char ***env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd[j])
	{

	}

}