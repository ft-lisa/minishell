#include "../minishell.h"

int     pwd1(t_list *pip)
{
        char *buf;
        char **str;

        str = ft_split(pip->cmd, ' ');
        if (str[1])
        {
                if (str[1][0] == '-' && str[1][1])
                {
                        ft_printf_fd(2, "bash: pwd: %c%c: invalid option\n", str[1][0], str[1][1]);
                        ifexit(pip, str);
                        return (2);
                }
        }
        buf = malloc(4097 * sizeof(char));
        getcwd(buf, 4096);
        printf("%s\n", buf);
        free(buf);
        ifexit(pip, str);
        return (0);
}
