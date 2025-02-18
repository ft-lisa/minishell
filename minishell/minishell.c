#include "minishell.h"

void exit_minishell()
{
    rl_clear_history();
    exit(0);
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
            exit_minishell();
        add_history(str);
        exe = creat_list(str, &env, argv, argc);
        exe->data->exit1 = error;
        // print_list(exe);
        error = exe1(exe);
    }
}

