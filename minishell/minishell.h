/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lismarti <lismarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:13:53 by smendez-          #+#    #+#             */
/*   Updated: 2025/03/07 11:40:32 by lismarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif
# include <fcntl.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
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

extern int g_sig;

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

            /* signaux */
 
void new(int signal);
void handler (int signal);
void her(int signal);
void parent_her(int signal);

            /* minishell */
            
int execution(t_list* exe, int error);
void exit_minishell(t_list *pip);

            /* utils */
            
/* utils1 */
int	isin(char *s, char c);
char	**cleanexit(char **a);
char	*cleanexit_int(int **a);
int	lvl2_len(int **fd);
char	*free_list(t_list *list);

/* utils2.c */
char *del_c(char *str, char c);
char	*get_path_command(char **paths, char *command);
char	*no_args_cmd(char *cmd);
int operator(char* txt);
void print_list(t_list *lst);
void print_split(char **str);

/* utils3 */
int pass_quote1(char quote, char* str, int i);
int size_delim(char **content, int j);
int double_strlen(char **content);
int all_space(char* line);
int count_pipes (char* str);

/* utils4 */

size_t	ft_strlen(const char *c);
int pass_quote_plus(char quote, const char* str, int i);
int search_exe1(char* content);
int search_exe2(char* content);
int	wait_all(int *pid, int len, t_list *pip);

            /* printf_fd-gnl */

int	ft_printf_fd(int fd, const char *format, ...);

            /* pipe */
/* check_exit */

int	ft_isalldigit(char *str);
int	check_long_long(char *str);
void	exit_minishell_error(t_list *pip);
int	check_exit(char **str, t_list *pip);

/* pipe_struct */

void	free_pip(t_list *pip);
char	**get_path(char *envp[]);
int	**ft_add_fd(int **fd, int len);
t_data	*init_exe2(t_data *pipex, char ***envp, char **argv, int count);
t_data	*init_exe(char ***envp, char **argv, int argc, int count);

/* pip_struct2 */

void	ft_close_all(int **fd);
int	ft_strrchr(const char *string, int searchedChar);
char	*recup_path(char *src);
void for_fork(int i, t_list* pip);
int	for_t2_and_t3(int stdo, t_list *pip, int t2);

/* pip_struct3 */

void	exe_build_single(t_list *pip, int t1, int t2);
void	type(t_list *pip, int t1, int t2);
void	exe_isolate(t_list *pip, int t1, int t2);
int exe1(t_list *pip, int i);


/* pipe_struct4 */
int     is_cmd(t_list *pip);
int     is_cmd_2d(t_list *pip);
char	*get_path_var(char *envp[], char *p1);
void     ifexit(t_list *pip, char **str);
void	ft_until_limiter(char *delimiter, int verbose, int *write_fd);

/* search_if_build */
int is_other(t_list *pip);
void exe_other(t_list *pip);

/* type1_to_3 */

void type1(t_list *pip);
void type1bis(t_list *pip);
void type2(t_list *pip);
void type3(t_list *pip); 

/* type5_to_7 */

void	quit_sigint(t_list* pip);
void type7(t_list *pip);
void type6(t_list *pip);
void type5(t_list *pip);

                /* lib */

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
char	**ft_split_exe1(char *s);
char	**ft_split_exe(char *s, char c);
int	ft_strcmp(char *s1, char *s2);
int     open_only_one_quote(char *str);
char	**ft_split_ope_bis(char const *s, char c, int i, int j);
size_t				ft_strlennull(const char *c);
int					ft_print_adress(void *ptr);
int					ft_sizenbr_base(long int numb, char *base, int unsigned1);
char				*ft_straddend1(char *malloc1, char *toadd, int index);
char				*ft_adresschar(void *ptr, char *mainmalloc, int index);
char				*ft_nbrcharhex(int nbr, char *base, char *mainmalloc, int index);
char				*ft_nbrchardec(int nbr, int unsigned1, char *mainmalloc, int index);
int					isformat(const char c);
int					ft_putstr_fd(char *s, int fd, int size);
char	**ft_split_txt(char const *s);

                /* creat_list */

/* check_operator */

int     chck1op(char *str);
int     isconsecutive_ops1_index(char *str, char *op);
int     isconsecutive_opsloop_index(char *str, char *op);
int     chck2op_type(char *str);
int     isconsecutive_ops1(char *str, char *op);
int     isconsecutive_opsloop(char *str, char *op);
int     chck2op(char *str);
char pick_quote(char *str);
char	*remove_first_quotes(char *str);
char	*remove_all_quotes(char *str);
int check_operator(char* str1);


/* clean_content_list */

void del_space(t_list *command);
void del_quotes(t_list *command);

/* creat_list */

char	**split_until(char *str, char c);
void fill_seven(t_list* new, char* content);
void fill_one_three(t_list* new, char* content);
void fill_six(t_list* new, char* content);
void fill_com_list(t_list *list, char** content);
void fill_ope_list(t_list *list, char** content);

/* expand */

int	replace_str(char **mainstr, char *before, char *after, int index);
int	isdollar_alone(char *str, int i);
int	indexto_skip_squotes(char *str, char c);
int	expand(char **cmd, char **env, int error);
int 	expand_vars(char **cmd, char ***env, int error);

/* init_list */

void init_list2(t_list *list);
t_list* init_list(int count, char ***envp, char **argv, int argc);
int     check_line(char **line, char ***envp, int error);
t_list *creat_list(char* line, char ***envp, char **argv, int argc);

                /* builtin */

/* cd */

int     error_cd(char **str, t_list *pip);
int cd_pwd(t_list *pip, char *buf);
int     cd1(t_list *pip);

/* echo */

int     echod(char *envp[], char *p1, int *i);
int	echo_var2(char *envp[], char *p1);
int     echoarg(char *str);
int     echo1(t_list *pip);

/* env */

int     env1(t_list *pip);

/* export */

static char	*remove_surrounding_quotes(const char *s);
static char	*process_backslashes(const char *s);
char	*parcing_export(char *str);
int     export_valid(char *str);
static char	*extract_key(char *s);
static int	update_existing(char ***env, char *key, char *new_val);
int	add_plus(char ***env, char *add);
void export1(t_list *pip, char **str);

/* pwd */

char     *pwd2(t_list *pip);
int     pwd1(t_list *pip);

/* unset */

int	rmv_str_2d(char ***str2, char *rmv);
int     unset_valid(char *str);
int     unset1(t_list *pip, char **str);

#endif //FT_H