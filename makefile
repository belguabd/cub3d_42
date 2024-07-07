
CC = cc -Wall -Wextra -Werror -g -fsanitize=address

NAME = cub3d
MLX_NAME = libmlx42.a
MLX_FLAGS = -Iinclude -lglfw -L"/Users/emagueri/.brew/opt/glfw/lib/"
SRC = main.c
OBJ = $(SRC:.c=.o)


all: $(NAME)

$(NAME): $(OBJ) cub3d.h
	$(CC) $(MLX_FLAGS) $(MLX_NAME) $(OBJ) -o $(NAME)

%.o: %.c cub3d.h
	$(CC) -c $< -o $@ 

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: all