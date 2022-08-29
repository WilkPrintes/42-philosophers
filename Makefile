NAME		:= philo

CC			:= clang

CCFLAGS		:= -Wall -Wextra -Werror

HEADER_DIR	:= ./header/

INCLUDE		:=	$(foreach directory, $(HEADER_DIR), -I $(directory))

SRC_DIR		:= ./src/

SRC_FILE	:=	philo.c philo_utils.c init.c times.c thead_func.c

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
	@valgrind -q --tool=helgrind ./philo 2 200 100 100

.PHONY: all fclean re
