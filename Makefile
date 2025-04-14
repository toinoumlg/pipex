NAME = pipex
CC = cc
CFLAGS = -Werror -Wextra -Wall
SRC_FILES = main.c free.c childs.c check.c
OBJ_FILES = $(SRC_FILES:%.c=$(OBJ_DIR)/%.o)
SRC_DIR = src/
OBJ_DIR = $(SRC_DIR)obj
HEADER= include/pipex.h
LIBFTPRINTF = libftprintf/libftprintf.a

all: libftprintf $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ_FILES) $(LIBFTPRINTF)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ_FILES) $(LIBFTPRINTF)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

libftprintf:
	make -C libftprintf

clean:
	rm -rf $(OBJ_DIR)
	make -C libftprintf clean

fclean: clean
	rm pipex
	make -C libftprintf fclean

re: fclean all

.PHONY: libftprintf all