# Makefile for the minishell project

# Compiler and flags
CC = gcc
CFLAGS = -g -Wall -Wextra -Werror

# Directories
SRC_DIR = src
LIBFT_DIR = lib/libft
OBJ_DIR = obj

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.c)
LIBFT = $(LIBFT_DIR)/libft.a

# Object files
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Output binary
NAME = minishell

# Phony targets
.PHONY: all clean fclean re

# Default target
all: $(NAME)

# Linking the executable
$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) -lreadline

# Compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)  # Create object directory if it doesn't exist
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up object files
clean:
	rm -rf $(OBJ_DIR)/*.o

# Clean up the library and executable
fclean: clean
	rm -f $(NAME)

# Rebuild the project
re: fclean all

