NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = dinner.c getters.c main.c parser.c routines.c safe_handling.c setters.c time.c\
		utils.c writing.c
OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(SRC)

all: $(NAME)

clean:
	rm -rf $(OBJ)

fclean:
	rm -rf $(NAME) $(OBJ)
	
re: fclean all