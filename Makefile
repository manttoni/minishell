NAME = minishell
FLAGS = -Wall -Wextra -Werror -g
LIBFT_DIR = lib/libft
LIBFT = lib/libft/libft.a
SRC =	src/array_utils.c \
	src/builtin.c \
	src/memory.c \
	src/environ.c \
	src/error.c \
	src/ft_cd.c \
	src/ft_exit.c \
	src/ft_export.c \
	src/here_doc.c \
	src/here_doc_utils.c \
	src/linked_list.c \
	src/linked_list_utils.c \
	src/minishell.c \
	src/path.c \
	src/process.c \
	src/redirection.c \
	src/run.c \
	src/signals.c \
	src/token.c \
	src/token_list.c \
	src/tokenizer.c \
	src/update_fd.c \
	src/utils.c \
	src/validation.c

OBJ = $(SRC:.c=.o)
CC = cc

all: $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(FLAGS) $(OBJ) $(LIBFT) -o $(NAME) -lreadline

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
