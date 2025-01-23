LIBFT_DIR = libft
NAME = $(LIBFT_DIR)/libft.a
EXEC = main

CC = gcc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -f

SRC_DIR = $(LIBFT_DIR)
SRCS = $(wildcard $(SRC_DIR)/**/*.c)
OBJS = $(SRCS:.c=.o)

MAIN = main.c
MAIN_OBJ = $(MAIN:.c=.o)

INCLUDES = -I$(SRC_DIR)

all: $(NAME) $(EXEC)

$(NAME): $(OBJS)
	$(AR) $@ $^

$(EXEC): $(NAME) $(MAIN_OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJS) $(MAIN_OBJ)

fclean: clean
	$(RM) $(NAME) $(EXEC)

re: fclean all

.PHONY: all clean fclean re

