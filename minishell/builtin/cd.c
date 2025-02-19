#include "../minishell.h"

int     error_cd(char **str)
{
        struct stat path_stat;
        
        if (stat(str[1], &path_stat) == -1)
                ft_printf_fd(2, "cd: no such file or directory: %s\n", str[1]);
        else
        {
                if (!S_ISDIR(path_stat.st_mode))
                        ft_printf_fd(2, "cd: not a directory: %s\n", str[1]);
                else
                        ft_printf_fd(2, "cd: permission denied: %s\n", str[1]);
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
        {
                ft_printf_fd(2, "bash: cd: too many arguments");
                ifexit(pip, str);
        }
        else if (ft_strcmp(str[0], "cd") == 0 && !str[1])
        {
                buf = get_path_var(*(pip->data->envp), "HOME");
                ret = chdir(buf);
                if (ret == -1)
                        ft_printf_fd(2, "bash: cd: HOME not set"); 
                ifexit(pip, str);
        }
        else if (ft_strcmp(str[0], "cd") == 0 && str[1])
        {
                ret = (chdir(str[1]));
                if (ret == -1)
                        error_cd(str);
                ifexit(pip, str);
        }
}
