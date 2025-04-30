PROG	= cub3d

SRCS 	= src/main.c src/check_args.c src/fill_map_vals.c src/check_map_size.c src/map_saving.c src/colors_convert.c src/mapping_check.c
OBJS 	= ${SRCS:.c=.o}
HEADER	= -Iincludes
MLX 	= -Lminilibx-linux -lmlx_Linux -Iminilibx-linux -lXext -lX11 -lm

CC 		= gcc
CFLAGS 	= -Wall -Wextra -g

.c.o:
		@${CC} ${CFLAGS} ${HEADER} -c $< -o $(<:.c=.o)

all: ${PROG}

${PROG}: ${OBJS}
		@echo "\033[33m----Compiling lib----"
		@make -s re -C ./libft
		@echo "LIBFT MADE"
		@${CC} ${OBJS} -Llibft -lft ${MLX} -o ${PROG}
		@echo "\033[32mcub3d compiled!ᕦ(\033[31m♥\033[32m_\033[31m♥\033[32m)ᕤ\n"

clean:
		@make clean -s -C ./libft
		@rm -f ${OBJS}

fclean: clean
		@make fclean -s -C ./libft
		@rm -f ${PROG} ${OBJS}
		@rm -rf libft/*.a libft/*.o libft/*.so
		@echo "\n\033[31mDeleting EVERYTHING! ⌐(ಠ۾ಠ)¬\n"

re: fclean all

.PHONY: all clean fclean re
