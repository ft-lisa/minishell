#include "minishell.h"

void exit_minishell(int signal)
{
    rl_clear_history();
    exit(0);
}

int main(void)
{
    char* str;

    signal(EOF, exit_minishell);
    while(1)
    {
        str = readline("minishell>");
        add_history(str);
        creat_list(str);
    }
}