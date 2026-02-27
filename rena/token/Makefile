NAME = minishell
cc = cc
CFLAGS = -Werror -Wextra -Wall

SRC = read.c token_extra.c token.c test.c helpers.c ../parser/parse.c ../parser/parser_helpers.c ../parser/testparse.c ../parser/utils.c edge_cases.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) 
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -lreadline

clean:
	rm -f $(OBJ)

fclean:
	rm -f $(NAME) $(OBJ)

re: fclean all