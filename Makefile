NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes
MLXFLAGS = -Lminilibx-linux -lmlx -L/usr/lib -lXext -lX11 -lm
LIBFT_PATH = ./libft
MLX_PATH = minilibx-linux
LIBFT = $(LIBFT_PATH)/libft.a
MLX = $(MLX_PATH)/libmlx.a

SRC = src/cub3d.c src/parse_map.c
OBJ = $(SRC:.c=.o)
INCLUDE_DIR = includes
RM = rm -f

# Domyślna kompilacja
all: $(NAME)

# Kompilowanie projektu
$(NAME): $(OBJ) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(MLX) $(MLXFLAGS)

# Kompilacja .c do .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Kompilacja libft
$(LIBFT):
	make -C $(LIBFT_PATH)

# Kompilacja MLX
$(MLX):
	git clone https://github.com/42Paris/minilibx-linux.git $(MLX_PATH) || true
	make -C $(MLX_PATH)

# Usuwanie plików .o
clean:
	$(RM) $(OBJ)
	make -C $(LIBFT_PATH) clean
	make -C $(MLX_PATH) clean

# Usuwanie wszystkiego
fclean: clean
	$(RM) $(NAME)

# Ponowna kompilacja
re: fclean all

.PHONY: all clean fclean re
