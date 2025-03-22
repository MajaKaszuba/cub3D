#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <string.h>
# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"

# define SCREEN_WIDTH 800
# define SCREEN_HEIGHT 600

typedef struct s_game
{
    void    *mlx;
    void    *win;
    char    *no_texture;
    char    *so_texture;
    char    *we_texture;
    char    *ea_texture;
    void    *no_img;
    void    *so_img;
    void    *we_img;
    void    *ea_img;
    int     tex_width;
    int     tex_height;
} t_game;

// Funkcje
void    init_window(t_game *game);
void    render_scene(t_game *game);

char *trim_newline(char *str);
void parse_map(t_game *game, char *filename);

#endif
