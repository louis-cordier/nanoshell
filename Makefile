NAME = nanoshell

SRC = src/main.c src/builtins.c src/exec.c src/utils.c
OBJ = $(SRC:src/%.c=obj/%.o)
OBJ_DIR = obj

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I./include

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

re: fclean all

.PHONY: all clean fclean re
