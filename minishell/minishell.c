#include "minishell.h"

int main(void)
{
    char* str;

    while(1)
    {
        str = readline("minishell>");
        add_history(str);
        creat_list(str);
    }
}