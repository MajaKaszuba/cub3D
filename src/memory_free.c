/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaszuba <mkaszuba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:00:10 by dtoszek           #+#    #+#             */
/*   Updated: 2025/05/19 14:43:42 by mkaszuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	map_error_free(t_game *game, int i)
{
	if (i == 1)
	{
		free_strings(game, NULL, NULL, 3);
		free_map(game);
		free_textures(game);
	}
	if (i == 2)
	{
		free_strings(game, NULL, NULL, 3);
		free_textures(game);
	}
}

void	free_nulled(char *line, char *trimmed, int i)
{
	if (i == 0)
	{
		free(line);
		free(trimmed);
		exit(0);
	}
	else if (i == 1)
	{
		free(line);
		exit(0);
	}
	else if (i == 2)
	{
		exit(0);
	}
}

void	free_strings(t_game *game, char *line, char *trimmed, int i)
{
	if (game->textures.no_path)
		free(game->textures.no_path);
	if (game->textures.we_path)
		free(game->textures.we_path);
	if (game->textures.ea_path)
		free(game->textures.ea_path);
	if (game->textures.so_path)
		free(game->textures.so_path);
	if (game->textures.f)
		free(game->textures.f);
	if (game->textures.c)
		free(game->textures.c);
	free_nulled(line, trimmed, i);
}

void	free_map(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map.highest_y)
	{
		free(game->map.valid_map[i]);
		i++;
	}
	free(game->map.valid_map);
}

void	free_textures(t_game *game)
{
	if (game->textures.no.img)
		mlx_destroy_image(game->mlx, game->textures.no.img);
	if (game->textures.so.img)
		mlx_destroy_image(game->mlx, game->textures.so.img);
	if (game->textures.ea.img)
		mlx_destroy_image(game->mlx, game->textures.ea.img);
	if (game->textures.we.img)
		mlx_destroy_image(game->mlx, game->textures.we.img);
	if (game->img.img)
		mlx_destroy_image(game->mlx, game->img.img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
		mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit(0);
}
