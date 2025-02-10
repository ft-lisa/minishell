#include "../minishell.h"

int     is_cmd(t_list *pip)
{
        char *no_a;
        char *get_p;
        int r;

        r = 1;
        if (!pip)
                 return (0);
        no_a = no_args_cmd(pip->cmd);
	get_p = get_path_command(pip->data->path, no_a);
        if (get_p[0] == '\0')
                r = 0;
        free(no_a);
        free(get_p);
        return (r);
}

int     is_cmd_2d(t_list *pip)
{
        char	**temp2;
        char *no_a;
        char *get_p;
        int r;

        r = 1;
        if (!pip)
                 return (0);
        temp2 = ft_split_exe(pip->cmd, ' ');
        no_a = no_args_cmd(temp2[1]);
	get_p = get_path_command(pip->data->path, no_a);
        if (get_p[0] == '\0')
                r = 0;
        free(no_a);
        free(get_p);
        cleanexit(temp2);
        return (r);
}

int is_other(char **str, t_list *pip)
{
        if (ft_strcmp(str[0], "cd") == 0)
                return (1);
        else if (ft_strcmp(str[0], "pwd") == 0)
                return (1);
        else if (ft_strcmp(str[0], "env") == 0 && is_cmd_2d(pip) == 0)
                return (printf("HEEEEERE\n\n\n"),1);
        return (0);
}

void exe_other(char **str, char **envp, t_list *pip)
{
        char *buf;
        int     i;



        if (ft_strcmp(str[0], "cd") == 0)
        {
            printf("here! \n");
            chdir(str[1]);
        }
        else if (ft_strcmp(str[0], "pwd") == 0)
        {
            buf = malloc(4097 * sizeof(char));
            getcwd(buf, 4096);
            printf("%s\n", buf);
            free(buf);
        }
        else if (ft_strcmp(str[0], "env") == 0 && str[1] == NULL)
        {
                i = 0;
                while (envp[i])
                        printf("%s\n", envp[i++]);
        }
        else if (ft_strcmp(str[0], "env") == 0)
                ft_printf_fd(2, "env: ʻ%s’: No such file or directory\n", str[1]);
}
