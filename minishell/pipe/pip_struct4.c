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

int is_other(t_list *pip)
{
        int     ret;
        char **str;

        ret = 0;
        if (isemptyor_spacetab(pip->cmd) == 1)
                return (0);
        str = ft_split_exe(pip->cmd, ' ');
        if (ft_strcmp(str[0], "cd") == 0)
                ret = 1;
        else if (ft_strcmp(str[0], "pwd") == 0)
                ret = 1;
        else if (ft_strcmp(str[0], "env") == 0 && is_cmd_2d(pip) == 0)
                ret = 1;
        else if (ft_strcmp(str[0], "echo") == 0)
                 ret = 1;
        else if (ft_strcmp(str[0], "exit") == 0)
                ret = 1;
        else if (ft_strcmp(str[0], "export") == 0)
                ret = 1;
        else if (ft_strcmp(str[0], "unset") == 0)
                ret = 1;
        cleanexit(str);
        return (ret);
}


char	*get_path_var(char *envp[], char *p1)
{
	int		i;
	int		j;
        int             len_p1;

	i = 0;
        len_p1 = ft_strlen(p1);
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] && envp[i][j] == p1[j])
			j++;
		if (j == len_p1 && envp[i][j] == '=')
		{
			return (envp[i] + j + 1);
		}
		i++;
	}
	return (NULL);
}

void     ifexit(t_list *pip, char **str)
{
        int     exit1;

        cleanexit(str);
        if (pip->data->n_cmd > 1)
        {
                exit1 = pip->data->new_exit;
                free_pip(pip);
                exit(exit1);
        }
}
 
void exe_other(t_list *pip)
{
        char *buf;
        int     i;
        char **str;

        str = ft_split_exe(pip->cmd, ' ');
        if (ft_strcmp(str[0], "cd") == 0)
                (cleanexit(str), cd1(pip));
        else if (ft_strcmp(str[0], "pwd") == 0)
                (cleanexit(str), pwd1(pip));
        else if (ft_strcmp(str[0], "env") == 0)
                (cleanexit(str), env1(pip));
        else if (ft_strcmp(str[0], "echo") == 0)
                (echo1(pip), ifexit(pip, str));
        else if (ft_strcmp(str[0], "export") == 0)
                (export1(pip, str), ifexit(pip, str));
        else if (ft_strcmp(str[0], "unset") == 0)
                (unset1(pip, str), ifexit(pip, str));
        else if (ft_strcmp(str[0], "exit") == 0)
        {
                if(check_exit(str, pip) == 1)
                {
                        (cleanexit(str), exit_minishell(pip));
                }
        }
}
