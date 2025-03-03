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
	if (!new)
		return (-1);
	while(i < index)
	{
		new[i] = (*mainstr)[i];
		i++;
	}
	i = 0;
	while(after && after[i])
	{
		new[index + i] = after[i];
		i++;
	}
	while((*mainstr)[index + len_b + 1])
	{
		new[index + len_a] = (*mainstr)[index + len_b + 1];
		index++;
	}
	new[index + len_a] = '\0';
	free(*mainstr);
	*mainstr = new;
	return (0);
}

int	isdollar_alone(char *str, int i)
{
	if (ft_isalnum(str[i + 1]) == 0 && str[i + 1] != '_' && str[i + 1] != '?')
		return (1);
	else
		return (0);

}

int	indexto_skip_squotes(char *str, char c)
{
	int	i;
	int	in_double;

	i = 0;
	in_double = 0;
	while (str[(i > 0) * (i - 1)] && str[i]) // if the 2dwhile reaches the end, we go i - 1, but not in the first interation
	{
		if (str[i] == '"')
		{
			in_double = !in_double;
			i++;
			continue;
		}
		if (!in_double && str[i] == '\'')
		{
			i++; 
			while (str[i] && str[i] != '\'')
				i++;
			continue;
		}
		if (isdollar_alone(str, i) == 1)
		{
			i++;
			continue;
		}
		if (str[i++] == c)
			return (i - 1);
	}
	return (-1);
}

int	expand(char **cmd, char **env, int error)
{
	char	*new;
	char	*temp;
	char	*temp2;
	int	i;

	i = indexto_skip_squotes(*cmd, '$');
        if (i == -1 || (*cmd)[i] == '\0')
                return (1);
	temp = copy_until_alnum_under(*cmd + i + 1);
	// printf("CHECKING COPY |%s| index |%d| strcmp |%d|\n\n", temp, i, ft_strcmp(temp, "$"));
	if (!temp)
		return (-1);
	if (ft_strcmp(temp, "?") == 0)
	{
		temp2 = ft_itoa(error);
		replace_str(cmd, temp, temp2, i);
		return (free(temp), free(temp2), 0);
	}
	if (isin_2d_equal(env, temp) == 1)
	{
		temp2 = get_path_var(env, temp);
		replace_str(cmd, temp, temp2, i);
		return (free(temp), 0);
	}
	replace_str(cmd, temp, NULL, i);
	return (free(temp), 0);
}

int 	expand_vars(char **cmd, char ***env, int error)
{
	int	check;
	int	j;
	char	*str;

	check = 0;
	j = 0;
	str = ft_strdup(*cmd);
	if (!str)
		return (-1);
	while (check == 0)
	{
		check = expand(&str, *env, error);
	}
	*cmd = str;
	if (isemptyor_spacetab(*cmd) == 1)
        {
		free(*cmd);
		check = -1;
	}
	return (check);
}
