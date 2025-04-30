#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <errno.h>
# include <stdio.h>
# include <math.h>

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define FOV 60 * (M_PI / 180)
# define MOVE_SPEED 0.1
# define ROTATE_SPEED 0.05
# define NUM_RAYS WIN_WIDTH
# define TILE_SIZE 1

typedef struct s_img
{
    void    *img;
    char    *addr;
    int     bpp;
    int     line_len;
    int     endian;
    int     width;  // Dodane pola dla szerokości tekstury
    int     height; // i wysokości tekstury
}   t_img;


typedef struct{
	t_img   NO;
    t_img   SO;
    t_img   WE;
    t_img   EA;
	char *no_path;
	char *so_path;
	char *we_path;
	char *ea_path;
	char *F;
	char *C;
	int *floor_color;
	int *ceeling_color;

}	t_texture;

typedef struct {
	char** valid_map;
	int lines_tilmap;
	int highest_x;
	int highest_y;
	int current_row;
}	t_map;

typedef struct {
	int is_player;
	float	px;
	float	py;
	float	pa;
}	t_player;

typedef struct{
	void	*mlx;
	void	*win;
	float	wall_hit_x;
	t_img	img;
	t_texture textures;
	t_map map;
	t_player player;
} t_game;


int 	check_args(char *map_name);
void 	fill_map_vals(t_game *game, char *str);
void 	check_x_and_y(t_game *game, char *str);
void  	alloc_map(t_game *game, char *str);
void 	color_convert(t_game *game);
void 	map_check(t_game *game);
bool 	is_player_value(char c);

#endif