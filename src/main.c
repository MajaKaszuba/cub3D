/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaszuba <mkaszuba@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:00:51 by mkaszuba          #+#    #+#             */
/*   Updated: 2025/05/05 15:48:51 by mkaszuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	start_game(t_game *game)
{
	game->textures.no_path = NULL;
	game->textures.so_path = NULL;
	game->textures.we_path = NULL;
	game->textures.ea_path = NULL;
	game->textures.F = NULL;
	game->textures.C = NULL;
	game->map.highest_x = 0;
	game->map.highest_y = 0;
	game->map.lines_tilmap = -1;
	game->player.is_player = 0;
}

void	start_texture(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	game->img.img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bpp,
			&game->img.line_len, &game->img.endian);
	load_textures(game);
	game->player.pa = 0;
}

void	put_pixel(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
	{
		dst = game->img.addr + (y * game->img.line_len + x * (
					game->img.bpp / 8));
		*(unsigned int *)dst = color;
	}
}

void	draw_vertical_line(t_game *game, int x, int height, int side)
{
	int				start;
	int				end;
	t_img			*texture;
	float			texture_step;
	float			texture_pos;
	int				y;
	int				tex_y;
	int				tex_x;
	unsigned int	color;

	start = (WIN_HEIGHT / 2) - (height / 2);
	end = (WIN_HEIGHT / 2) + (height / 2);
	if (start < 0)
		start = 0;
	if (end >= WIN_HEIGHT)
		end = WIN_HEIGHT - 1;
	if (side == 0)
		texture = &game->textures.NO;
	else if (side == 1)
		texture = &game->textures.SO;
	else if (side == 2)
		texture = &game->textures.EA;
	else
		texture = &game->textures.WE;
	texture_step = (float)texture->height / height;
	texture_pos = (start - WIN_HEIGHT / 2 + height / 2) * texture_step;
	y = 0;
	while (y < WIN_HEIGHT)
	{
		if (y < start)
			put_pixel(game, x, y, game->textures.ceeling_color);
		else if (y >= start && y < end)
		{
			tex_y = (int)texture_pos & (texture->height - 1);
			tex_x = game->wall_hit_x * texture->width;
			if (tex_x < 0)
				tex_x = 0;
			if (tex_x >= texture->width)
				tex_x = texture->width - 1;
			color = get_texture_color(texture, tex_x, tex_y);
			put_pixel(game, x, y, color);
			texture_pos += texture_step;
		}
		else
			put_pixel(game, x, y, game->textures.floor_color);
		y++;
	}
}

void	cast_rays(t_game *game)
{
	float	ray_angle;
	float	angle_step;
	int		x;

	ray_angle = game->player.pa - (FOV / 2);
	angle_step = FOV / NUM_RAYS;
	x = 0;
	while (x < NUM_RAYS)
	{
		float ray_dir_x = cos(ray_angle);
		float ray_dir_y = sin(ray_angle);

		int map_x = (int)game->player.px;
		int map_y = (int)game->player.py;

		float delta_dist_x = fabsf(1 / ray_dir_x);
		float delta_dist_y = fabsf(1 / ray_dir_y);

		int step_x, step_y;
		float side_dist_x, side_dist_y;

		if (ray_dir_x < 0) {
			step_x = -1;
			side_dist_x = (game->player.px - map_x) * delta_dist_x;
		} else {
			step_x = 1;
			side_dist_x = (map_x + 1.0 - game->player.px) * delta_dist_x;
		}
		if (ray_dir_y < 0) {
			step_y = -1;
			side_dist_y = (game->player.py - map_y) * delta_dist_y;
		} else {
			step_y = 1;
			side_dist_y = (map_y + 1.0 - game->player.py) * delta_dist_y;
		}
		int hit = 0;
		int side = -1; // 0 = vertical (E/W), 1 = horizontal (N/S)
		while (!hit)
		{
			if (side_dist_x < side_dist_y) {
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			} else {
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}

			if (game->map.valid_map[map_y][map_x] == '1')
				hit = 1;
		}
		float perp_wall_dist;
		if (side == 0)
			perp_wall_dist = (map_x - game->player.px + (1 - step_x) / 2) / ray_dir_x;
		else
			perp_wall_dist = (map_y - game->player.py + (1 - step_y) / 2) / ray_dir_y;
		int line_height = (int)(WIN_HEIGHT / (perp_wall_dist + 0.0001));
		// Get exact wall hit location (for texture x)
		float wall_x;
		if (side == 0)
			wall_x = game->player.py + perp_wall_dist * ray_dir_y;
		else
			wall_x = game->player.px + perp_wall_dist * ray_dir_x;
		wall_x -= floorf(wall_x);
		game->wall_hit_x = wall_x;
		// Determine texture based on side and ray direction
		int texture_side;
		if (side == 0)  // Vertical wall
			texture_side = (ray_dir_x > 0) ? 2 : 3; // East or West
		else            // Horizontal wall
			texture_side = (ray_dir_y > 0) ? 1 : 0; // South or North
		draw_vertical_line(game, x, line_height, texture_side);
		ray_angle += angle_step;
		x++;
	}
}

int	update(t_game *game)
{
	cast_rays(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (0);
}

void	rotate_player(t_game *game, float direction)
{
	game->player.pa += direction * ROTATE_SPEED;
}

void	move_player(t_game *game, float move_x, float move_y)
{
	float	new_px;
	float	new_py;
	float	check_y;
	float	check_x;

	new_px = game->player.px + move_x * MOVE_SPEED;
	new_py = game->player.py + move_y * MOVE_SPEED;
	if (move_x > 0)
		check_x = new_px + 0.1f;
	else
		check_x = new_px - 0.1f;
	if (game->map.valid_map[(int)game->player.py][(int)check_x] != '1')
		game->player.px = new_px;
	if (move_y > 0)
		check_y = new_py + 0.1f;
	else
		check_y = new_py - 0.1f;
	if (game->map.valid_map[(int)check_y][(int)game->player.px] != '1')
		game->player.py = new_py;
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == 65307)
		exit(0);
	if (keycode == 65361)
		rotate_player(game, -1);
	else if (keycode == 65363)
		rotate_player(game, 1);
	else if (keycode == 119)
		move_player(game, cos(game->player.pa), sin(game->player.pa));
	else if (keycode == 115)
		move_player(game, -cos(game->player.pa), -sin(game->player.pa));
	else if (keycode == 100)
		move_player(game, -sin(game->player.pa), cos(game->player.pa));
	else if (keycode == 97)
		move_player(game, sin(game->player.pa), -cos(game->player.pa));
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		printf("Error: Valid input: ./cub3d map_name.cub");
		return (0);
	}
	check_args(argv[1]);
	start_game(&game);
	fill_map_vals(&game, argv[1]);
	printf("map val:%s", game.textures.no_path);
	start_texture(&game);
	check_x_and_y(&game, argv[1], 0);
	alloc_map(&game, argv[1]);
	color_convert(&game);
	map_check(&game);
	mlx_loop_hook(game.mlx, update, &game);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_loop(game.mlx);
	return (0);
}
