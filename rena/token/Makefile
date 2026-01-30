NAME = minishell
cc = cc
CFLAGS = -Werror -Wextra -Wall -g

SRC = read.c token_extra.c token.c test.c helpers.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) 
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean:
	rm -f $(NAME) $(OBJ)

re: fclean all