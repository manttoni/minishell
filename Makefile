NAME = minishell
FLAGS = -g -Wall -Wextra -Werror
LIBFT_DIR = /lib/libft
LIBFT = lib/libft/libft.a
SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
CC = cc

all: $(LIBFT) $(OBJ)
	$(CC) $(FLAGS) $(OBJ) $(LIBFT) -o $(NAME) -lreadline

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) all

clean:
	rm $(OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm $(NAME)
	$(MAKE) -C fclean

re: fclean all

.PHONY: all clean fclean re
