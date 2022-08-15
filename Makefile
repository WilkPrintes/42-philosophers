NAME		:= philosophers

CC			:= clang

CCFLAGS		:= -Wall -Wextra -Werror

LIBFT		:= ./includes/libft/libft.a

LIBFT_PATH	:= ./includes/libft/

LIBFT_FLAGS	:= -L $(LIBFT_PATH) -lft

HEADER_DIR	:= ./header/ ./includes/libft/

INCLUDE		:=	$(foreach directory, $(HEADER_DIR), -I $(directory))

SRC_DIR		:= ./src/

SRC_FILE	:=	philo.c

SRC			:=	$(foreach file, $(SRC_FILE), $(SRC_DIR)$(file))

all: $(NAME)

$(NAME): $(LIBFT) $(SRC)
	@$(CC) -g $(CCFLAGS) $(SRC) -o $@ $(INCLUDE) $(LIBFT_FLAGS) -lreadline
	@echo "\033[0;32mPhilosophers (>‿◠)\033[0m"

$(LIBFT):
	@echo compilando libft...
	@make -s -C $(LIBFT_PATH)

fclean: clean
	@rm -rf $(NAME)
	@echo apagando libft
	@make fclean -s -C $(LIBFT_PATH)
	@echo "\033[0;31mPhilosophers deleted (ㆆ_ㆆ)\033[0m"

clean:
	@make clean -s -C $(LIBFT_PATH)
	@rm -rf *.o

re: fclean all

$(OBJ_DIR):
	@mkdir -p $@

norma:
	@norminette ./

leaks:
	@valgrind --leak-check=full --track-origins=yes --suppressions=readline.supp --show-leak-kinds=all --trace-children=yes ./minishell

.PHONY: all fclean re
