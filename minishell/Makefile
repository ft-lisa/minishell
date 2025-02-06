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
# Source files in different folders (wildcards)
ROOT_SRC    := $(wildcard *.c)
LIB_SRC     := $(wildcard lib/*.c)
PRINTF_SRC  := $(wildcard printf_fd/*.c)
UTILS_SRC   := $(wildcard utils/*.c)

# ------------------------------------------------------------------------------
# For the exe version: use exe1.c as main, so exclude minishell.c from the root
SRC_EXE    := $(filter-out minishell.c, $(ROOT_SRC)) $(LIB_SRC) $(PRINTF_SRC) $(UTILS_SRC)
OBJS_EXE   := $(patsubst %.c, $(TRASH)/%.o, $(SRC_EXE))

# For the mini version: use minishell.c as main, so exclude exe1.c from the root
SRC_MINI   := $(filter-out exe1.c, $(ROOT_SRC)) $(LIB_SRC) $(PRINTF_SRC) $(UTILS_SRC)
OBJS_MINI  := $(patsubst %.c, $(TRASH)/%.o, $(SRC_MINI))

# Executable names
NAME_EXE   := exe
NAME_MINI  := minishell

#===============================================================================
# Animation: a quick dot animation during the build!
animate:
	@echo -n "$(YELLOW)Building"
	@for i in 1 2 3 4 5; do \
		echo -n "."; \
		sleep 0.3; \
	done; \
	echo -e " $(GREEN)Done!$(NC)"

#===============================================================================
# Targets

# Default target builds both versions
all: mini exe

#------------------------------------------------------------------------------
# Build the exe version (uses exe1.c as main)
exe: $(NAME_EXE)
	@echo -e "$(GREEN)Executable '$(NAME_EXE)' is ready!$(NC)"

$(NAME_EXE): $(OBJS_EXE)
	@$(MAKE) animate
	$(CC) $(OBJS_EXE) $(CFLAGS) $(LIBS) -o $(NAME_EXE)

#------------------------------------------------------------------------------
# Build the mini version (uses minishell.c as main)
mini: $(NAME_MINI)
	@echo -e "$(GREEN)Executable '$(NAME_MINI)' is ready!$(NC)"

$(NAME_MINI): $(OBJS_MINI)
	@$(MAKE) animate
	$(CC) $(OBJS_MINI) $(CFLAGS) $(LIBS) -o $(NAME_MINI)

#===============================================================================
# Pattern rule: Compile any .c file into its corresponding .o file inside .trash.
# It creates the target directory if it doesn't exist.
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
	rm -f $(NAME_EXE) $(NAME_MINI)

re: fclean all

#===============================================================================
.PHONY: all animate clean fclean re exe mini
