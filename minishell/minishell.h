#ifndef MINISHELL_H
# define MINISHELL_H
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <sys/types.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <term.h>
# include <curses.h>

typedef struct s_list
{
	char		*cmd;
    int     index;
    int     exe1;
    int     exe2;
    char    *if_file1;
    char    *if_file2;
    struct s_list	*next;
}					t_list;

                /* creat_list.c */

int count_node(char* line);
t_list creat_list(char* line);

char	**ft_split(char const *s);


#endif