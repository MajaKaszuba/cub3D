/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaszuba <mkaszuba@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 12:53:17 by mkaszuba          #+#    #+#             */
/*   Updated: 2025/05/05 16:42:32 by mkaszuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# define FOV 1.0471975512  // 60 stopni w radianach
# define MOVE_SPEED 0.1
# define ROTATE_SPEED 0.05
# define NUM_RAYS WIN_WIDTH
# define TILE_SIZE 1

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_texture
{
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	char	*F;
	char	*C;
	int		floor_color;
	int		ceeling_color;
	t_img	NO;
	t_img	SO;
	t_img	WE;
	t_img	EA;
}	t_texture;

typedef struct s_map
{
	char	**valid_map;
	int		lines_tilmap;
	int		highest_x;
	int		highest_y;
	int		current_row;
}	t_map;

typedef struct s_player
{
	int		is_player;
	float	px;
	float	py;
	float	pa;
}	t_player;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	float		wall_hit_x;
	t_img		img;
	t_texture	textures;
	t_map		map;
	t_player	player;
}	t_game;

//casting_rays.c
void	put_pixel(t_game *game, int x, int y, int color);
void	draw_vertical_line(t_game *game, int x, int height, int side);
void	cast_rays(t_game *game);

//check_args.c
int		check_args(char *map_name);

//check_map_size.c
void	check_x_and_y(t_game *game, char *str, int i);

//colors_convert.c
int		convert(char *str);
void	color_convert(t_game *game);

//fill_map_vals_utils.c
char	*ft_strcpy(char *dst, const char *src);
int		ft_isspace(char c);
int		is_only_whitespace(const char *str, bool map_status);

//fill_map_vals_logic.c
bool	check_for_all(t_game *game);
void	find_id(char *str, t_game *game);
bool	is_map_part(t_game *game, char *str);
bool	is_not_map_format(const char *str);
void	fill_map_vals(t_game *game, char *str);

//load_textures.c
void	load_texture(void *mlx, t_img *texture, char *path);
void	load_textures(t_game *game);
unsigned int	get_texture_color(t_img *texture, int x, int y);

//main.c
void	start_game(t_game *game);
void	start_texture(t_game *game);
int		main(int argc, char **argv);

//map_flood_check.c
bool	zero_flood_check(t_game *game, int j, int i);
void	zero_check(t_game *game);
void	map_check(t_game *game);
bool	x_check_dirs(t_game *game, int x, int y);

//map_saving.c
char	*ft_strcpy_2(char *dst, const char *src, int size);
char	**allocate_2d_char_array(int rows, int cols);
void	alloc_map(t_game *game, char *str);

//mapping_check.c
bool	is_player_value(char c);
bool	x_check(t_game *game, int x, int y);
bool	player_in_map(t_game *game, int pos_x, int pos_y);
void	check_boundaries_x(t_game *game);
void	check_boundaries_y(t_game *game);

//player_control.c
void	rotate_player(t_game *game, float direction);
void	move_player(t_game *game, float move_x, float move_y);
int		key_press(int keycode, t_game *game);

#endif