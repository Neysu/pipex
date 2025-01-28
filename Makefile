# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Directories
LIBFT_DIR = libft
SRC_DIR = .
OBJ_DIR = obj

# Source files
LIBFT_SRCS = $(wildcard $(LIBFT_DIR)/**/*.c)
SRCS = $(SRC_DIR)/pipex.c $(SRC_DIR)/exec.c $(SRC_DIR)/utils.c

# Object files
LIBFT_OBJS = $(patsubst $(LIBFT_DIR)/%.c, $(OBJ_DIR)/%.o, $(LIBFT_SRCS))
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Target executable
NAME = pipex

# Rules
all: $(NAME)

$(NAME): $(LIBFT_OBJS) $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(LIBFT_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
