#include "../minishell.h"


char     *pwd2(t_list *pip)
{
        char *buf;
        char *err;
        char **str;

        buf = malloc(4097 * sizeof(char));
        err = getcwd(buf, 4096);
        if (!err)
        {
                ft_printf_fd(2, "chdir: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n");
                free(buf);
                return (NULL);
        }
        return (buf);
}

int     pwd1(t_list *pip)
{
        char *buf;
        char *err;
        char **str;

        str = ft_split(pip->cmd, ' ');
        if (!str)
                return (-1);
        if (str[1])
        {
                if (str[1][0] == '-' && str[1][1])
                {
                        ft_printf_fd(2, "bash: pwd: %c%c: invalid option\n", str[1][0], str[1][1]);
                        pip->data->new_exit = 2;
                        ifexit(pip, str);
                        return (2);
                }
        }
        buf = malloc(4097 * sizeof(char));
        err = getcwd(buf, 4096);
        if (err)
                printf("%s\n", buf);
        else
        {
                ft_printf_fd(2, "pwd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n");
                pip->data->new_exit = 1;
        }
        free(buf);
        ifexit(pip, str);
        return (0);
}
