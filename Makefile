# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/08 15:05:47 by ana-cast          #+#    #+#              #
#    Updated: 2024/07/25 01:30:46 by jorvarea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
##                               COMPILATION INFO                             ##
################################################################################

NAME = minishell
LIBFT = lib/libft/

# Check if gcc is installed
HAS_GCC := $(shell command -v gcc 2> /dev/null)

# Check if clang is installed
HAS_CLANG := $(shell command -v clang 2> /dev/null)

ifdef HAS_CLANG
  CC = clang
else ifdef HAS_GCC
  CC = gcc
else
  $(error No compiler found)
endif

FLAGS = -Wall -Wextra -Werror -g
RM = rm -f
MINISHELL = include/
INCLUDE = -lreadline -L ./lib/libft -lft
DEPS = -I include -I $(LIBFT)/include

################################################################################
##                              SOURCES AND OBJECTS                           ##
################################################################################

SRC = src/main.c \
	src/init_signals.c \
	src/signal_handling.c \

SRC_PARSER = src/parser/parser.c \
	src/parser/init.c \
	src/parser/env.c \
	src/parser/tokenizer/split_parser.c \
	src/parser/tokenizer/quotes.c \
	src/parser/lexer/redirs.c \
	src/parser/lexer/token_list.c \
	src/parser/lexer/update_token_list.c \
	src/parser/utils/error.c \
	src/parser/utils/free_utils.c \
	src/parser/utils/get_type.c \
	src/parser/utils/print_shell.c \
	src/parser/utils/print_utils.c \
	src/parser/utils/struct_nodes.c \
	src/parser/utils/utils.c

SRC_EXEC = src/exec/exec.c \
	src/exec/exec_utils.c \
	src/exec/parenthesis.c \
	src/exec/exec_single_cmd.c \
	src/exec/execute_cmd.c \
	src/exec/execute_redir.c \
	src/exec/heredoc.c \
	src/exec/heredoc_utils.c \
	src/exec/execute_bin.c \
	src/exec/utils/update_exit_status_process.c \
	src/exec/utils/flag_utils.c \
	src/exec/utils/is_directory.c \
	src/exec/utils/env_utils.c \
	src/exec/utils/update_envp.c \
	src/exec/utils/error_utils.c \
	src/exec/utils/error_utils2.c \
	src/exec/utils/safe_malloc.c \
	src/exec/utils/safe_realloc.c \
	src/exec/utils/safe_dup2.c \
	src/exec/utils/safe_dup.c \
	src/exec/utils/safe_fork.c \
	src/exec/utils/safe_pipe.c \
	src/exec/utils/ft_strrep.c \
	src/exec/utils/utils.c \
	src/exec/built-ins/echo.c \
	src/exec/built-ins/pwd.c \
	src/exec/built-ins/env.c \
	src/exec/built-ins/cd.c \
	src/exec/built-ins/export.c \
	src/exec/built-ins/unset.c \
	src/exec/built-ins/exit.c \
	src/exec/expansions/expand_cmd.c \
	src/exec/expansions/expand_wildcards.c \
	src/exec/expansions/matching_pattern.c \
	src/exec/expansions/replace.c

OBJECTS = $(SRC:.c=.o)
OBJ_PAR = $(SRC_PARSER:.c=.o)
OBJ_EXEC = $(SRC_EXEC:.c=.o)

#BONUS_SR = \
	
#BONUS_OB = $(BONUS_SR:.c=.o)

################################################################################
##                                    COLORS                                 ##
################################################################################

END=\033[0m
BOLD=\033[1m
GREEN=\033[0;32m
RED=\033[0;31m
BLUE=\033[0;34m
YELLOW=\033[33m
MAGENTA=\033[35m
TURQUOISE=\033[36m

################################################################################
##                                     RULES                                  ##
################################################################################

all : head libft $(NAME)

head :
	@echo "$(MAGENTA)"
	@echo "\t███    ███ ██ ███    ██ ██ ███████ ██   ██ ███████ ██      ██      "
	@echo "\t████  ████ ██ ████   ██ ██ ██      ██   ██ ██      ██      ██      "
	@echo "\t██ ████ ██ ██ ██ ██  ██ ██ ███████ ███████ █████   ██      ██      "
	@echo "\t██  ██  ██ ██ ██  ██ ██ ██      ██ ██   ██ ██      ██      ██      "
	@echo "\t██      ██ ██ ██   ████ ██ ███████ ██   ██ ███████ ███████ ███████ "
	@echo ""
	@echo "\t        42MLG: by ana-cast && jorvarea"
	@echo "\tProyect: \033[36m minishell $(MAGENTA)"
	@echo "\tCommands:\033[36m all clean fclean re bonus $(BLUE)"
	@echo "\t🛠   Compiler: $(CC) $(END)\n"

libft :
	@make bonus -s -C $(LIBFT)

$(NAME) : line $(OBJECTS) $(OBJ_PAR) $(OBJ_EXEC)
	@echo "✦ ---------------------- ✦$(END)"
	@$(CC) $(FLAGS) $(OBJECTS) $(OBJ_PAR) $(OBJ_EXEC) $(INCLUDE) -o $(NAME)

bonus : all line $(BONUS_OB)
	@echo "✦ ---------------------- ✦$(END)"
	@$(CC) $(FLAGS) $(BONUS_OB) $(INCLUDE) -o $(NAME)

%.o : %.c $(MINISHELL)
	@$(CC) $(FLAGS) -c $< -o $@ $(DEPS)
	@echo "$(GREEN)  ✓ Compiled: $(notdir $<)"

line :
	@echo "$(GREEN) $(BOLD)"
	@echo "  COMPILING MINISHELL...$(END) $(GREEN)"
	@echo "✦ ---------------------- ✦"

clean :
	@printf "\n$(YELLOW) 🗑   Removing objects$(END)"
	@$(RM) $(OBJECTS) $(OBJ_PAR) $(OBJ_EXEC) $(BONUS_OB) 
	@echo "$(GREEN)\r  ✓  $(RED)Removed  objects from $(NAME) $(END)"
	@make clean -s -C $(LIBFT)

fclean: clean
	@printf "$(YELLOW) 🗑   Removing $(NAME) $(END)"
	@$(RM) $(NAME)
	@make fclean -s -C $(LIBFT)
	@echo "$(GREEN)\r  ✓  $(RED)Removed  $(NAME) $(END)\n"

re :
	@$(MAKE) -s fclean
	@clear
	@$(MAKE) -s all

.PHONY: all bonus clean fclean re