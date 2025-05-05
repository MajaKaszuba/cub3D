/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting_rays.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaszuba <mkaszuba@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 16:29:46 by mkaszuba          #+#    #+#             */
/*   Updated: 2025/05/05 16:52:00 by mkaszuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
