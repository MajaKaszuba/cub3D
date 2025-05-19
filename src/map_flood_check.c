/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_flood_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoszek <dtoszek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 16:13:18 by mkaszuba          #+#    #+#             */
/*   Updated: 2025/05/16 11:14:44 by dtoszek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	zero_flood_check(t_game *game, int j, int i)
{
	game->map.valid_map[i][j] = 'O';
	if (game->map.valid_map[i][j -1] == '0')
		zero_flood_check(game, j - 1, i);
	else if (game->map.valid_map[i][j - 1] == 'X')
		map_error_free(game, 1);
	if (game->map.valid_map[i][j + 1] == '0')
		zero_flood_check(game, j + 1, i);
	else if (game->map.valid_map[i][j + 1] == 'X')
		map_error_free(game, 1);
	if (game->map.valid_map[i - 1][j] == '0')
		zero_flood_check(game, j, i - 1);
	else if (game->map.valid_map[i - 1][j] == 'X')
		map_error_free(game, 1);
	if (game->map.valid_map[i + 1][j] == '0')
		zero_flood_check(game, j, i + 1);
	else if (game->map.valid_map[i + 1][j] == 'X')
		map_error_free(game, 1);
	return (1);
}

void	zero_check(t_game *game)
{
	int	i;
	int	j;

	i = 1;
	while (i < game->map.highest_y - 1)
	{
		j = 1;
		while (j < game->map.highest_x - 1)
		{
			if (game->map.valid_map[i][j] == '0')
				zero_flood_check(game, j, i);
			if (!is_player_value(game->map.valid_map[i][j]))
			{
				player_in_map(game, j, i);
				game->player.is_player++;
				game->player.px = (float)j;
				game->player.py = (float)i;
			}
			if (game->player.is_player > 1)
				map_error_free(game, 1);
			j++;
		}
		i++;
	}
}

void	map_check(t_game *game)
{
	int	i;

	check_boundaries_x(game);
	check_boundaries_y(game);
	zero_check(game);
	i = 0;
	while (i < game->map.highest_y)
	{
		printf("%s\n", game->map.valid_map[i]);
		i++;
	}
}

bool	x_check_dirs(t_game *game, int x, int y)
{
	if (x > 0)
	{
		if (game->map.valid_map[y][x - 1] == 'X')
			x_check(game, x - 1, y);
		else if (game->map.valid_map[y][x - 1] == is_player_value(
			game->map.valid_map[y][x - 1]))
			map_error_free(game, 1);
		else if (game->map.valid_map[y][x - 1] == '0')
			map_error_free(game, 1);
	}
	if (x < game->map.highest_x - 1)
	{
		if (game->map.valid_map[y][x + 1] == 'X')
			x_check(game, x + 1, y);
		else if (game->map.valid_map[y][x + 1] == 'P')
			map_error_free(game, 1);
		else if (game->map.valid_map[y][x + 1] == '0')
			map_error_free(game, 1);
	}
	return (1);
}
