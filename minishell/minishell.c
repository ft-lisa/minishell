#include "minishell.h"

int sig_g = 0;

void exit_minishell(t_list *pip)
{
    long long exit_val;
    int exit_code;
    char **cmd;

    cmd = ft_split_exe1(pip->cmd);
    if (!cmd[1])
    {
        free_pip(pip);
        rl_clear_history();
        exit(0);
    }
    exit_val = ft_atoll(cmd[1]);
    exit_code = (int)(exit_val % 256);
    // printf("val |%lld| code |%d| cmd |%s|\n\n", exit_val, exit_code, cmd[1]);
    if (exit_code < 0)
        exit_code += 256;
    rl_clear_history();
    free_pip(pip);
    exit(exit_code);
}

void handler (int signal)
{
    write(1, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
    sig_g = signal;
}

void new(int signal)
{
    write(1, "\n", 1);
    rl_on_new_line();
    sig_g = signal;
    return ;
}
void her(int signal)
{ 
    write(1, "\n", 1);
    close(0);
    sig_g = signal;
    return ;
}
void parent_her(int signal)
{ 
    sig_g = signal;
    return ;
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
    signal(SIGQUIT, SIG_IGN);
    while(1)
    {
        signal(SIGINT, handler);
        str = readline("minishell> ");
        if (str == NULL)
        {
            printf("exit\n");
            rl_clear_history();
            exit(1);
        }
        add_history(str);
        if (sig_g == 2)
        {
            error = 130;
            sig_g = 0;
        }
        if (check_line(&str, &env, error) == 1)
            continue;
        exe = creat_list(str, &env, argv, argc);
        // print_list(exe);
        if(exe)
        {
            signal(SIGINT, new);
            exe->data->exit1 = error;
            error = exe1(exe);
        }
    }
}

