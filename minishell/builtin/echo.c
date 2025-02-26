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
        if (isin_2d_equal(envp, copy) == 0)
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

int     echoarg(char *str)
{
        int     i;

        i = 1;
        // printf("str |%s| cmp |%d|", str, ft_strncmp(str, "-n", 2));
        if (ft_strncmp(str, "-n", 2) != 0)
                return (0);
        while (str[i])
        {
                if (str[i] != 'n')
                        return (0);
                i++;
        }
        return (1);
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
        if (str[1] && echoarg(str[1]) == 1)
                j++;
        while(str[j])
        {
                if (str[j] && echoarg(str[j]) == 1)
                {
                        j++;
                        continue ;
                }
                ft_printf_fd(1, "%s", str[j]);
                j++;
                if (str[j])
                        ft_printf_fd(1, " ");
        }
        if (!str[1] || echoarg(str[1]) != 1)
                ft_printf_fd(1, "\n");
        cleanexit(str);
        return (0);
}
