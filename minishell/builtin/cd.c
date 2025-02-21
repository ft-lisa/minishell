#include "../minishell.h"

int     error_cd(char **str)
{
        struct stat path_stat;

        if (str[1][0] == '-' && str[1][1])
                ft_printf_fd(2, "bash: cd: %c%c: invalid option\n", str[1][0], str[1][1]);
        if (stat(str[1], &path_stat) == -1)
                ft_printf_fd(2, "bash: cd: No such file or directory: %s\n", str[1]);
        else
        {
                if (!S_ISDIR(path_stat.st_mode))
                        ft_printf_fd(2, "bash: cd: Not a directory: %s\n", str[1]);
                else
                        ft_printf_fd(2, "bash: cd: Permission denied: %s\n", str[1]);
        }
}

int     cd1(t_list *pip)
{
        char **str;
        char *buf;
        int     ret;

        str = ft_split(pip->cmd, ' ');
        if (!str)
                return (-1);
        if (str_len_2d(str) > 2)
                ft_printf_fd(2, "bash: cd: too many arguments\n");
        else if (ft_strcmp(str[0], "cd") == 0 && !str[1])
        {
                buf = get_path_var(*(pip->data->envp), "HOME");
                if (buf)
                        ret = chdir(buf);
                if (buf == NULL || ret == -1)
                        ft_printf_fd(2, "bash: cd: HOME not set\n");
        }
        else if (ft_strcmp(str[0], "cd") == 0 && str[1])
        {
                ret = (chdir(str[1]));
                if (ret == -1)
                {
                        printf("error_cd");
                        error_cd(str);
                }
        }
        ifexit(pip, str);
}
