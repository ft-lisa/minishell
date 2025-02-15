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

// void export1(t_list *pip, char **str)
// {
//         int     i;

//         i = 0;
//         if (!str[1])
//                 while (pip->data->envp[i])
//                         printf("%s\n", pip->data->envp[i++]);
//         else
//         {
                
//         }
// }

int is_other(t_list *pip)
{
        int     ret;
        char **str;

        ret = 0;
        str = ft_split(pip->cmd, ' ');
        if (ft_strcmp(str[0], "cd") == 0)
                ret = 1;
        else if (ft_strcmp(str[0], "pwd") == 0)
                ret = 1;
        else if (ft_strcmp(str[0], "env") == 0 && is_cmd_2d(pip) == 0)
                ret = 1;
        else if (ft_strcmp(str[0], "echo") == 0 && ft_strncmp(str[1], "$", 1) == 0 && ft_strlen(str[1]) > 1)
                ret = 1;
        else if (ft_strcmp(str[0], "exit") == 0)
                ret = 1;
        else if (ft_strcmp(str[0], "export") == 0)
                ret = 1;
        cleanexit(str);
        return (ret);
}

int	echo_var(char *envp[], char *p1)
{
	int		i;
	int		j;
        int             k;
        int             len_p1;

	i = 0;
        k = 0;
        len_p1 = ft_strlen(p1);
        while (len_p1 > -1)
        {
                if(isalnum(p1[len_p1 - 1]) == 0)
                {
                        len_p1--;
                        k++;
                }
                else
                        break;
        }
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] == p1[j])
			j++;
		if (j == len_p1)
		{
			printf("%s",envp[i] + j + 1);
                        printf("%s", p1 + len_p1);
                        return (1);
		}
		i++;
	}
        printf("%s", p1);
        return (0);
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
		while (envp[i][j] == p1[j])
			j++;
		if (j == len_p1)
		{
			return (envp[i] + j + 1);
		}
		i++;
	}
	return (NULL);
}

void exe_other2(char **str, char **envp, t_list *pip)
{
        char *var;
        char **temp;
        int     i;
        int     j;

        j = 1;
        if (ft_strcmp(str[0], "echo") == 0)
        {
                while(str[j])
                {
                        temp = ft_split(str[j], '$');
                        i = 0;
                        while (temp[i])
                        {
                                echo_var(envp ,temp[i++]);
                        }
                        j++;
                        cleanexit(temp);
                }
                printf("\n");
                (free_pip(pip), cleanexit(str), exit(0));
        }
        else if (ft_strcmp(str[0], "exit") == 0)
                (free_pip(pip), cleanexit(str), exit(0));
}

void exe_other(t_list *pip)
{
        char *buf;
        int     i;
        char **str;

        str = ft_split(pip->cmd, ' ');
        if (ft_strcmp(str[0], "cd") == 0 || str[1])
        {
                (chdir(str[1]), cleanexit(str), free_pip(pip), exit(0));
        }
        else if (ft_strcmp(str[0], "pwd") == 0)
        {
            buf = malloc(4097 * sizeof(char));
            getcwd(buf, 4096);
            printf("%s\n", buf);
            free(buf);
            (free_pip(pip), cleanexit(str), exit(0));
        }
        else if (ft_strcmp(str[0], "env") == 0 && str[1] == NULL)
        {
                i = 0;
                while (pip->data->envp[i])
                        printf("%s\n", pip->data->envp[i++]);
                (free_pip(pip), cleanexit(str), exit(0));
        }
        else if (ft_strcmp(str[0], "env") == 0)
        {
                ft_printf_fd(2, "env: ʻ%s’: No such file or directory\n", str[1]);
                (free_pip(pip), cleanexit(str), exit(0));
        }
        else
                exe_other2(str, pip->data->envp, pip);
}

void exe_other2_isolate(char **str, char **envp, t_list *pip)
{
        char *var;
        char **temp;
        int     i;
        int     j;

        j = 1;
        if (ft_strcmp(str[0], "echo") == 0)
        {
                while(str[j])
                {
                        temp = ft_split(str[j], '$');
                        i = 0;
                        while (temp[i])
                        {
                                //printf("R:%s", temp[i]);
                                echo_var(envp ,temp[i++]);
                        }
                        j++;
                        cleanexit(temp);
                }
                cleanexit(str);
                printf("\n");
        }
        else if (ft_strcmp(str[0], "exit") == 0)
                (free_pip(pip), cleanexit(str), exit(0));
}

void exe_other_isolate(t_list *pip)
{
        char *buf;
        int     i;
        char **str;

        str = ft_split_exe(pip->cmd, ' ');
        if (ft_strcmp(str[0], "cd") == 0 && str[1])
        {
                (chdir(str[1]));
                cleanexit(str);
        }
        else if (ft_strcmp(str[0], "pwd") == 0)
        {
            buf = malloc(4097 * sizeof(char));
            getcwd(buf, 4096);
            printf("%s\n", buf);
            free(buf);
            cleanexit(str);
        }
        else if (ft_strcmp(str[0], "env") == 0 && str[1] == NULL)
        {
                i = 0;
                while (pip->data->envp[i])
                        printf("%s\n", pip->data->envp[i++]);
                cleanexit(str);
        }
        else if (ft_strcmp(str[0], "env") == 0)
        {
                ft_printf_fd(2, "env: ʻ%s’: No such file or directory\n", str[1]);
                cleanexit(str);
        }
        else
        {
                exe_other2_isolate(str, pip->data->envp, pip);
        }
}
