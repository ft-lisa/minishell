#include "../minishell.h"

char *del_c(char *str, char c)
{
        int i;
        int k;
        char *new_s;

        i = 0;
        k = 0;
        if (!str || str == NULL)
                return (NULL);
        while(str[i])
                if (str[i++] != c)
                        k++;
        if (k == 0)
                return (str);
        new_s = malloc((k + 1) * sizeof(char));
        if(!new_s)
                return (NULL);
        k = 0;
        i = 0;
        while(str[i])
        {
        if (str[i] != c) 
                new_s[k++] = str[i];
        i++;
        }
        new_s[k] = '\0';
        free(str);
        return (new_s);
}

char	*get_path_command(char **paths, char *command)
{
	int		i;
	int		j;
	char	*temp;
	char	*temp2;
	char	*path;

	i = 0;
	j = -1;
	if ((command == NULL) || (paths[0] == NULL))
		return (ft_calloc(1, 1));
	while (j != 0 && paths[i])
	{
		temp = ft_strjoin(paths[i++], "/");
		temp2 = ft_strjoin(temp, command);
		j = access(temp2, F_OK);
		if (j == 0)
			path = ft_strdup(temp2);
		free(temp);
		free(temp2);
	}
	if (j == 0)
		return (path);
	return (ft_calloc(1, 1));
}

char	*no_args_cmd(char *cmd)
{
	int		i;
	int		j;
	char	*first_cmd;

	i = 0;
	j = 0;
	if (cmd == NULL)
		return (ft_strdup("Error"));
	while (cmd[i] && cmd[i] != ' ')
		i++;
	if (ft_strlen(cmd) == (size_t)i)
		return (ft_strdup(cmd));
	first_cmd = malloc((i + 1) * sizeof(char));
	if (!first_cmd)
		return (NULL);
	while (j < i)
	{
		first_cmd[j] = cmd[j];
		j++;
	}
	first_cmd[j] = '\0';
	return (first_cmd);
}
