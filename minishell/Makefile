# Compiler settings
CC      := gcc
CFLAGS  := -g -Werror
LIBS    := -lreadline -lncurses

# Directories
TRASH   := .trash

# Source files
ROOT_SRC = minishell.c signaux.c

LIB_SRC = lib/ft_itoa.c \
          lib/ft_split.c \
          lib/ft_split_exe_bis.c \
          lib/ft_split_exe.c \
          lib/ft_split_mini.c \
          lib/ft_split_ope.c \
          lib/ft_strcmp.c \
          lib/libft1.c \
          lib/libft2.c \
          lib/libft3.c \
          lib/libft4.c \
          lib/libft5.c \
          lib/libft6.c \
          lib/split_ope_bis.c \
          lib/split_txt.c \
          lib/trim.c

PRINTF_SRC = printf_fd-gnl/ft_printf_fd1.c \
             printf_fd-gnl/ft_printf_fd2.c \
             printf_fd-gnl/ft_printf_fd3.c \
             printf_fd-gnl/ft_printf_fd4.c

UTILS_SRC = utils/utils1.c \
            utils/utils2.c \
            utils/utils3.c \
            utils/utils4.c

BUILTIN_SRC = builtin/cd.c \
              builtin/echo.c \
              builtin/env.c \
              builtin/export2.c \
              builtin/export3.c \
              builtin/export.c \
              builtin/pwd.c \
              builtin/unset.c

PIPE_SRC = pipe/check_exit.c \
           pipe/execution.c \
           pipe/for_build.c \
           pipe/pip_struct2.c \
           pipe/pip_struct3.c \
           pipe/pip_struct4.c \
           pipe/pip_struct.c \
           pipe/type1_to_3.c \
           pipe/type5_to_7.c

CREAT_LIST_SRC = creat_list/check_operator2.c \
                 creat_list/check_operator3.c \
                 creat_list/check_operator.c \
                 creat_list/clean_content_list.c \
                 creat_list/creat_list.c \
                 creat_list/expand2.c \
                 creat_list/expand.c \
                 creat_list/fill_7_1_3.c \
                 creat_list/fill_com.c \
                 creat_list/init_list_2.c \
                 creat_list/init_list.c

# Use minishell.c as the main file (ignore exe1.c if present)
SRC = $(filter-out exe1.c, $(ROOT_SRC)) $(LIB_SRC) $(PRINTF_SRC) $(UTILS_SRC) $(BUILTIN_SRC) $(PIPE_SRC) $(CREAT_LIST_SRC)
OBJS = $(patsubst %.c, $(TRASH)/%.o, $(SRC))

# Executable name
NAME := minishell

# Default target
all: $(NAME)

# Build minishell
$(NAME): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(LIBS) -o $(NAME)

# Compile .c files into .o files in .trash
$(TRASH)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up object files and executables
clean:
	rm -rf $(TRASH)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
