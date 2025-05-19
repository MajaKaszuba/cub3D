/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaszuba <mkaszuba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:53:33 by mkaszuba          #+#    #+#             */
/*   Updated: 2025/05/19 14:42:05 by mkaszuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	load_texture(void *mlx, t_img *texture, char *path)
{
	texture->img = mlx_xpm_file_to_image(
			mlx, path, &texture->width, &texture->height);
	if (!texture->img)
	{
		printf("Error: Failed to load texture %s\n", path);
		exit(1);
	}
	texture->addr = mlx_get_data_addr(
			texture->img, &texture->bpp, &texture->line_len, &texture->endian);
}

void	load_textures(t_game *game)
{
	if (!game->textures.no_path || !game->textures.so_path
		|| !game->textures.we_path || !game->textures.ea_path)
	{
		printf("Błąd: Brak ścieżki do tekstury!\n");
		exit(1);
	}
	load_texture(game->mlx, &game->textures.no, game->textures.no_path);
	load_texture(game->mlx, &game->textures.so, game->textures.so_path);
	load_texture(game->mlx, &game->textures.we, game->textures.we_path);
	load_texture(game->mlx, &game->textures.ea, game->textures.ea_path);
}

unsigned int	get_texture_color(t_img *texture, int x, int y)
{
	char	*pixel;
	int		color;

	if (!texture->addr || x < 0 || y < 0
		|| x >= texture->width || y >= texture->height)
		return (0);
	pixel = texture->addr + (y * texture->line_len + x * (texture->bpp / 8));
	color = *(unsigned int *)pixel;
	return (color);
}
