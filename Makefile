SRC=main.c builtins.c 
NAME=nanoshell
FLAGS=-Wall -Wextra -Werror 
FLAGS=-Wall -Wextra 


all: $(SRC)
	gcc $(SRC) -o $(NAME) $(FLAGS) 



