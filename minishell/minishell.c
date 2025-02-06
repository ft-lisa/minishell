#include "minishell.h"

void exit_minishell()
{
    rl_clear_history();
    exit(0);
}

int main(void)
{
    char* str;
    
    while(1)
    {
        str = readline("minishell>");
        if (str == NULL)
            exit_minishell();   
        add_history(str);
        creat_list(str);
    }
}