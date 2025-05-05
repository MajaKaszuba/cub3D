/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_size.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaszuba <mkaszuba@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:09:33 by mkaszuba          #+#    #+#             */
/*   Updated: 2025/05/05 13:15:42 by mkaszuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	check_x_and_y(t_game *game, char *str, int i)
{
	char	*line;
	int		fd_sizes;
	int		temp;

	fd_sizes = open(str, O_RDONLY);
	while (i++ < game->map.lines_tilmap)
	{
		line = get_next_line(fd_sizes);
		free(line);
	}
	line = get_next_line(fd_sizes);
	if (!line)
		printf("Error No Map");
	temp = ft_strlen(line) - 1;
	while (1)
	{
		if (!line)
			break ;
		game->map.highest_y++;
		if (game->map.highest_x < temp)
			game->map.highest_x = temp;
		free(line);
		line = get_next_line(fd_sizes);
	}
	close(fd_sizes);
}
