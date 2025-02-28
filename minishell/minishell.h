/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smendez- <smendez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:13:53 by smendez-          #+#    #+#             */
/*   Updated: 2025/02/28 14:02:28 by smendez-         ###   ########.fr       */
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
# include <errno.h>
# include <signal.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct s_pipex
{
	char			***envp;
	char			**path;
	int				**fd;
	int				*pid;
	char			**v;
    int             n_cmd;
    char            **content;
    int             exit1;
    int             new_exit;
}					t_data;

typedef struct s_list

{
	char		*cmd;
    int     index;
    int     exe1;
    int     exe2;
    char    *if_file1;
    char    *if_file2;
    char    **delim;
    t_data *data;
    struct s_list	*next;
}					t_list;

// exe

int exe1(t_list *pip);
void	free_pip(t_list *pip);
int	**ft_add_fd(int **fd, int len);
int	wait_all(int *pid, int len, t_list *pip);
void	ft_close_all(int **fd);
char	*get_path_command(char **paths, char *command);
char	*get_path_var(char *envp[], char *p1);
char	*no_args_cmd(char *cmd);
void type1(t_list *pip);
void type2(t_list *pip);
void type3(t_list *pip);
void type5(t_list *pip);
void type6(t_list *pip);
void type7(t_list *pip);
void	exe_isolate(t_list *pip, int t1, int t2);
int is_other(t_list *pip);
int     is_cmd(t_list *pip);
void exe_other(t_list *pip);
void exe_other_isolate(t_list *pip);
void     ifexit(t_list *pip, char **str);
int	check_exit(char **str, t_list *pip);

// builtin
int     cd1(t_list *pip);
void export1(t_list *pip, char **str);
int     pwd1(t_list *pip);
char     *pwd2(t_list *pip);
int     env1(t_list *pip);
int     echo1(t_list *pip);
int     unset1(t_list *pip, char **str);
void  exit_minishell(t_list *pip);

// utils 
int operator(char* txt);
void print_list(t_list *lst);
int pass_quote1(char quote, char* str, int i);
int size_delim(char **content, int j);
int double_strlen(char **content);
int search_exe2(char* content);
int search_exe1(char* content);

// libft
char	*ft_strjoin(char const *s1, const char *s2);
void	*ft_calloc(size_t nitems, size_t size);
char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *c);
char	*cleanexit_int(int **a);
char	**ft_split(char const *s, char c);
char	*ft_strtrim(char const *s1, const char *set);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
int	str_len_2d(char **str);
char	**strdup_2d(char **s);
int     add_last_2d(char ***str2, char *add);
int     rmv_str_2d(char ***str2, char *rmv);
char	*ft_strchr(const char *str, int search_str);
int	ft_isalnum_under_plus(char *str);
char	*ft_strcpy(char *dest, char *src);
char	*ft_strcat(char *dest, const char *src);
char	*ft_strncpy(char *dest, char *src, unsigned int n);
char	*ft_strstr(char *str, char *to_find);
void	*ft_memcpy(void *dest_str, const void *src_str, size_t n);
char	*copy_until(char *str, char c);
char	*copy_until_one(char *str, char *c);
char	*copy_until_alnum_under(char *str);
int	isin_2d_delim(char **str, char *check, char delim);
int	isin_2d_equal(char **str, char *check);
int	ft_isalnum(int c);
int	count_c(char *str, char c);
int	isemptyor_spacetab(char *str);
long long ft_atoll(const char *s);
char	*ft_itoa(int k);
// int pass_quote(char quote, const char* str, int i);

// various
int	isin(char *s, char c);
char	**ft_split_exe(char *s, char c);
char	**cleanexit(char **a);
int	lvl2_len(int **fd);
char	*free_list(t_list *list);
char *del_c(char *str, char c);
int all_space(char* line);
int count_pipes (char* str);


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

// get next line modified
char				*ft_straddend(char *malloc1, char *toadd, int buffersize);
char				*ft_resetsc(char *base);
char				*ft_strdup2(const char *s, int line);
char				*get_next_line(int fd);
size_t				sl(const char *c);
void				*ft_calloc2(size_t nitems, size_t size);
char				*ft_realloc(char *oldlloc, size_t buffersize);
void	            ft_until_limiter(char *argv, int verbose);
int					isin1(const char *set, const char c, int buffersize);
int					ft_strcmp(char *s1, char *s2);

// list creation
char	**ft_split_txt(char const *s);
char	**ft_split_quotes(char const *s, char c);
char	**ft_split_ope_bis(char const *s, char c);
char	**ft_split_puts(char const *s);
int pass_quote_plus(char quote, const char* str, int i);
char	**ft_split_ope(char const *s);
int count_node(char* line);
t_list *creat_list(char* line, char ***envp, char **argv, int argc);
t_list* init_list(int count, char ***envp, char **argv, int argc);
t_data	*init_exe(char ***envp, char **argv, int argc, int count);
void fill_file_list(t_list *list, char** content);
int fill_com_list2(t_list *new, char** content, int j, int max);
void fill_ope_list(t_list *list, char** content);
void fill_com_list(t_list *list, char** content);

//check list
int     chck2op(char *str);
int check_operator(char* str);
int     open_only_one_quote(char *str);
int     check_line(char **line, char ***envp, int error);


//clean content list
void del_space(t_list *command);
void del_quotes(t_list *command);

// parcing
char	*parcing_export(char *str);
int 	expand_vars(char **cmd, char ***env, int error);

// temp
void print_list(t_list *lst);

#endif //FT_H