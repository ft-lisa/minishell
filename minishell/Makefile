SRC =  creat_list.c\
		minishell.c\
		split_txt.c\
		ft_split.c\
		

OBJS = $(SRC:.c=.o)


NAME = minishell
CC = gcc
# FLAGS = -Wall -Wextra -Werror

FLAGS = -lreadline -lncurses

$(NAME) :
		$(CC)  $(SRC) -Iincludes -lreadline -lncurses -g -o $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re