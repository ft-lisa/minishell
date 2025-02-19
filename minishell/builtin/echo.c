#include "../minishell.h"

int     echod(char *envp[], char *p1, int *i)
{
        int		k;
	int		j;
        char	*temp;
        char    *copy;

        copy = copy_until(p1 + 1, '$');
        if (!copy)
		return (-2);
        temp = ft_strjoin(copy, "=");
	if (!temp)
		return (-2);
        *i += ft_strlen(copy) + 1;
        if (isin_2d(envp, copy) == 0)
        {
                (free(copy), free(temp));
                return (-1);
        }
        j = ft_strlen(temp);
        k = 0;
        while (envp[k] && ft_strncmp(envp[k], temp, j) !=0)
                k++;
        printf("%s",envp[k] + j);
        (free(copy), free(temp));
        return (0);
}

int	echo_var2(char *envp[], char *p1)
{
	int		i;
        int             k;
        int             len_p1;

	i = 0;
        k = 0;
        len_p1 = ft_strlen(p1);

        while (p1[i])
        {
                if (p1[i] == '$')
                {
                        k = echod(envp, p1 + i, &i);
                }
                else if (p1[i] != '\\')
                                printf("%c", p1[i++]);
                else
                        i++;
        }
        return (k);
}

int     echo1(t_list *pip)
{
        int     i;
        int     j;
        int     error;
        char **str;

        str = ft_split(pip->cmd, ' ');
        j = 1;
        error = 0;
        if (str[1] && ft_strcmp(str[1], "-n") == 0)
                j++;
        while(str[j])
        {
                error = echo_var2(*pip->data->envp, str[j]);
                j++;
                if (str[j] && error != -1)
                        printf(" ");
        }
        if (!str[1] || ft_strcmp(str[1], "-n") != 0)
                printf("\n");
        cleanexit(str);
        return (0);
}
