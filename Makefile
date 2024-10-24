NAME = minishell
FLAGS = -Wall -Wextra -Werror -g
LIBFT_DIR = lib/libft
LIBFT = lib/libft/libft.a
SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
CC = cc

all: $(LIBFT) $(OBJ)
	$(CC) $(LAGS) $(OBJ) $(LIBFT) -o $(NAME) -lreadline

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) all

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
