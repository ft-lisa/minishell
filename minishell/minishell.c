#include "minishell.h"

void exit_minishell()
{
    rl_clear_history();
    exit(0);
}

int main(int argc, char** argv, char** envp)
{
    char* str;
    if (argc != 1)
        return(1);
    while(1)
    {
        str = readline("minishell> ");
        if (str == NULL || ft_strcmp(str, "exit") == 0)
            exit_minishell();   
        add_history(str);
        ft_printf_fd(1," str: |%s|\n\n", str);
        //creat_list(str, envp, argv, argc);
        exe1(argc, argv, envp);
    }
}