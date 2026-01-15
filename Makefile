SCR=last.c
NAME=nanoshell
FLAGS=-Wall -Wextra -Werror


all: $(SCR)
	gcc $(FLAGS) -o $(NAME) $(SCR)

