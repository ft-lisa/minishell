# Disable built-in implicit rules
.SUFFIXES:

#===============================================================================
# Color variables
RED     := \033[0;31m
GREEN   := \033[0;32m
YELLOW  := \033[1;33m
BLUE    := \033[0;34m
MAGENTA := \033[0;35m
CYAN    := \033[0;36m
NC      := \033[0m

#===============================================================================
# Compiler settings
CC      := gcc
CFLAGS  := -g
LIBS    := -lreadline -lncurses

#===============================================================================
# Directories
TRASH   := .trash

#===============================================================================
# Source files (wildcards)
ROOT_SRC    	:= $(wildcard *.c)
LIB_SRC     	:= $(wildcard lib/*.c)
PRINTF_SRC  	:= $(wildcard printf_fd-gnl/*.c)
UTILS_SRC   	:= $(wildcard utils/*.c)
BUILTIN_SRC		:= $(wildcard builtin/*.c)
PIPE_SRC		:= $(wildcard pipe/*.c)
CREAT_LIST_SRC	:= $(wildcard creat_list/*.c)

# Use minishell.c as the main file (ignore exe1.c if present)
SRC       := $(filter-out exe1.c, $(ROOT_SRC)) $(LIB_SRC) $(PRINTF_SRC) $(UTILS_SRC) $(BUILTIN_SRC) $(PIPE_SRC) $(CREAT_LIST_SRC)
OBJS      := $(patsubst %.c, $(TRASH)/%.o, $(SRC))

# Executable name
NAME      := minishell

#===============================================================================
# Animation target (phoney)
.PHONY: animate
animate:
	@echo -n "$(YELLOW)Building"
	@for i in 1 2 3 4 5; do \
		echo -n "."; \
	done; \
	echo -e " $(GREEN)Done!$(NC)"

#===============================================================================
# Default target builds the minishell executable
all: $(NAME)
	@echo -e "$(GREEN)Executable '$(NAME)' is ready!$(NC)"

# Build minishell (first run animate, then link object files)
$(NAME): animate $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(LIBS) -o $(NAME)

#===============================================================================
# Pattern rule: Compile any .c file into its corresponding .o file in .trash.
$(TRASH)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo -e "$(BLUE)Compiling $< into $@...$(NC)"
	$(CC) $(CFLAGS) -c $< -o $@

#===============================================================================
# Clean up object files and executables
clean:
	@echo -e "$(MAGENTA)Cleaning object files in '$(TRASH)'...$(NC)"
	rm -rf $(TRASH)

fclean: clean
	@echo -e "$(MAGENTA)Removing executables...$(NC)"
	rm -f $(NAME)

re: fclean all

#===============================================================================
.PHONY: all clean fclean re