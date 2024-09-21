# Makefile for the minishell project

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Directories
SRC_DIR = src
LIB_DIR = lib/libft

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.c)
LIBS = $(LIB_DIR)/libft.a

# Output binary
NAME = minishell

# Phony targets
.PHONY: all clean fclean re

# Default target
all: $(NAME)

# Linking the executable
$(NAME): $(SRCS) $(LIBS)
	$(CC) $(CFLAGS) -o $(NAME) $(SRCS) $(LIBS) -lreadline

# Clean up object files
clean:
	rm -f $(LIB_DIR)/*.o $(SRC_DIR)/*.o

# Clean up the library and executable
fclean: clean
	rm -f $(NAME)

# Rebuild the project
re: fclean all

