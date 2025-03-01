#include "minishell.h"

int sig_g = 0;

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

void handler (int signal)
{
    write(1, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
    sig_g = signal;
    return ;
}

void new(int signal)
{
    write(1, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
    sig_g = signal;
    return ;
}

void init_signal(struct sigaction* sa, struct sigaction* sc, struct sigaction* scn)
{
    sa->sa_handler = SIG_IGN;     
    sc->sa_handler = handler;
    scn->sa_handler = new;
    scn->sa_flags = 0;
    sa->sa_flags = 0;
    sc->sa_flags = 0;             
    sigemptyset(&sa->sa_mask);
    sigemptyset(&sc->sa_mask);
    sigemptyset(&scn->sa_mask);
}

int main(int argc, char** argv, char** envp)
{
    char *str;
    char **env;
    t_list *exe;
    int error;
    struct sigaction sa;
    struct sigaction sc;
    struct sigaction scn;


    if (argc != 1)
        return(1);
    env = strdup_2d(envp);
    error = 0;
    init_signal(&sa, &sc, &scn);
    sigaction(SIGQUIT, &sa, NULL);
    while(1)
    {
        sigaction(SIGINT, &sc, NULL);
        str = readline("minishell> ");
        if (str == NULL)
        {
            printf("exit\n");
            rl_clear_history();
            exit(1);
        }
        add_history(str);
        // printf("line |%c = %d|", str[0], str[0]);
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
            sigaction(SIGINT, &scn, NULL);
            exe->data->exit1 = error;
            error = exe1(exe);
        }
    }
}

