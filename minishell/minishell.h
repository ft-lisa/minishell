/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smendez- <smendez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:13:53 by smendez-          #+#    #+#             */
/*   Updated: 2025/02/06 13:26:34 by smendez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <fcntl.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

// lisa

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

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct s_pipex
{
	char			**envp;
	char			**path;
	int				**fd;
	int				*pid;
	char			**v;
}					t_pipex;

typedef struct s_list
{
	char		*cmd;
    int     index;
    int     exe1;
    int     exe2;
    char    *if_file1;
    char    *if_file2;
    char			**envp;
	char			**path;
	int				**fd;
	int				*pid;
	char			**v;
    struct s_list	*next;
}					t_list;

t_list	*init_pipex(t_list *pipex, char **envp, char **argv, int argc);
void	free_pip(t_pipex *pip);
int	**ft_add_fd(int **fd, int len);
int	wait_all(int *pid, int len);
void	ft_close_all(int **fd);

// libft
char	*ft_strjoin(char const *s1, const char *s2);
void	*ft_calloc(size_t nitems, size_t size);
char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *c);
char	*cleanexit_int(int **a);
char	**ft_split(char const *s, char c);

// various
int	isin(char *s, char c);
char	**ft_split_exe(char *s, char c);
char	**cleanexit(char **a);
int	lvl2_len(int **fd);


// printf_fd
int					ft_printf_fd(int fd, const char *format, ...);
char				*ft_nbrchardec(int nbr, int unsigned1, char *mainmalloc, int index);
int					ft_sizenbr_base(long int numb, char *base, int unsigned1);
char				*ft_straddend1(char *malloc1, char *toadd, int index);
char				*ft_nbrcharhex(int nbr, char *base, char *mainmalloc, int index);
size_t				ft_strlennull(const char *c);
int					ft_print_adress(void *ptr);
int					ft_putstr_fd(char *s, int fd, int size);
char				*ft_adresschar(void *ptr, char *mainmalloc, int index);
int					isformat(const char c);

// lisa
char	**ft_split_txt(char const *s);
int count_node(char* line);
t_list *creat_list(char* line, char **envp, char **argv, int argc);


#endif //FT_H