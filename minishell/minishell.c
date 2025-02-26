#include "minishell.h"

void exit_minishell(t_list *pip)
{
    long long exit_val;
    int exit_code;
    char **cmd;

    cmd = ft_split(pip->cmd, ' ');
    if (!cmd[1])
    {
        free_pip(pip);
        rl_clear_history();
        exit(0);
    }
    exit_val = ft_atoll(cmd[1]);
    exit_code = (int)(exit_val % 256);
    if (exit_code < 0)
        exit_code += 256;
    rl_clear_history();
    free_pip(pip);
    exit(exit_code);
}

int main(int argc, char** argv, char** envp)
{
    char *str;
    char **env;
    t_list *exe;
    int error;

    if (argc != 1)
        return(1);
    env = strdup_2d(envp);
    error = 0;
    while(1)
    {
        str = readline("minishell> ");
        if (str == NULL)
        {
            rl_clear_history();
            exit(1);
        }
        add_history(str);
        if (check_line(&str, &env, error) == 1)
            continue;
        exe = creat_list(str, &env, argv, argc);
        if(exe)
        {
            exe->data->exit1 = error;
            // print_list(exe);
            error = exe1(exe);
        }
    }
}

