#include "minishell.h"

void exit_minishell()
{
    rl_clear_history();
    exit(0);
}

int main(int argc, char** argv, char** envp)
{
    char *str;
    char **str2;
    t_list *exe;
    if (argc != 1)
        return(1);
    while(1)
    {
        str = readline("minishell> ");
        if (str == NULL || ft_strcmp(str, "exit") == 0)
            exit_minishell();
        add_history(str);
        exe = creat_list(str, envp, argv, argc);
        str2 = ft_split(str, ' ');
        if (is_other(str2, exe) == 1)
            {
                exe_other(str2, envp, exe);
            }
        else
            exe->data->exit1 = exe1(exe);
        cleanexit(str2);
    }
}