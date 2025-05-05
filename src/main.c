/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaszuba <mkaszuba@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:00:51 by mkaszuba          #+#    #+#             */
/*   Updated: 2025/05/05 16:32:11 by mkaszuba         ###   ########.fr       */
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

int	update(t_game *game)
{
	cast_rays(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
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
