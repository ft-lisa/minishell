# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
#include <signal.h>

// compile avec gcc test.c -o test -lreadline -lncurses

char    *get_line()
{
    char *line;

    line = NULL;
    if (line)
    {
        free(line);
        line = NULL;
    }
    line = readline("Minishell>");
    if (line)
        add_history(line);
    return (line);
}

void    sig_handler(int signum)
{
    if (signum == SIGINT)
    {
        printf("\n");
        rl_on_new_line();
        rl_replace_line("", 1);
        rl_redisplay();
    }
}

int main(void)
{
    char    *line;

    while(1)
    {signal(SIGINT, sig_handler);
    line = get_line();}
}









