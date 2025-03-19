# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkaszuba <mkaszuba@student.42warsaw.pl>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/18 15:13:53 by mkaszuba          #+#    #+#              #
#    Updated: 2025/03/18 16:25:57 by mkaszuba         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes
MLXFLAGS = -Lincludes/minilibx -lm -lmlx -L/usr/lib/X11 -lXext -lX11
LIBFT_PATH = ./libft
MLX_PATH = minilibx-linux
LIBFT = $(LIBFT_PATH)/libft.a
MLX = $(MLX_PATH)/libmlx.a

SRC = src/cub3d.c
OBJ = $(SRC:.c=.o)
INCLUDE_DIR = includes
RM = rm -f

# Domyślny cel
all: $(NAME)

# Kompilowanie i budowanie projektu
$(NAME): $(OBJ) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(MLX) $(MLXFLAGS)

# Kompilacja plików .c do .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Kompilacja biblioteki libft (jeśli nie została jeszcze zbudowana)
$(LIBFT):
	make -C $(LIBFT_PATH)

# Kompilacja biblioteki MLX (jeśli nie została jeszcze zbudowana)
$(MLX):
	make -C $(MLX_PATH)

# Usuwanie obiektów
clean:
	$(RM) $(OBJ)
	make -C $(LIBFT_PATH) clean
	make -C $(MLX_PATH) clean

# Usuwanie obiektów i pliku wynikowego
fclean: clean
	$(RM) $(NAME)
	make -C $(LIBFT_PATH) fclean
	# Usuwanie pliku libmlx.a nie jest wymagane, więc usuwamy to
	# make -C $(MLX_PATH) fclean

# Kompilowanie na nowo
re: fclean all

.PHONY: all clean fclean re
