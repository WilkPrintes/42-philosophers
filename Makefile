NAME		:= philosophers

CC			:= clang

CCFLAGS		:= -Wall -Wextra -Werror

HEADER_DIR	:= ./header/

INCLUDE		:=	$(foreach directory, $(HEADER_DIR), -I $(directory))

SRC_DIR		:= ./src/

SRC_FILE	:=	philo.c philo_utils.c

SRC			:=	$(foreach file, $(SRC_FILE), $(SRC_DIR)$(file))

all: $(NAME)

$(NAME): $(SRC)
	@$(CC) -g $(CCFLAGS) $(SRC) -o $@ $(INCLUDE) -pthread
	@echo "\033[0;32mPhilosophers (>‿◠)\033[0m"

fclean: clean
	@rm -rf $(NAME)
	@echo "\033[0;31mPhilosophers deleted (ㆆ_ㆆ)\033[0m"

clean:
	@rm -rf *.o

re: fclean all

$(OBJ_DIR):
	@mkdir -p $@

norma:
	@norminette ./

leaks:
	@valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --trace-children=yes ./philosophers

.PHONY: all fclean re
