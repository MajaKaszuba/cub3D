/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaszuba <mkaszuba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:07:23 by mkaszuba          #+#    #+#             */
/*   Updated: 2025/05/19 15:26:51 by mkaszuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_args(char *map_name)
{
	int	fd;

	if (ft_strnstr(map_name + ft_strlen(map_name) - 4, ".cub", 4) == NULL)
	{
		printf("Wrong map extension proper map name: map_name.cub\n");
		exit(0);
	}
	fd = open(map_name, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		exit(-1);
	}
	close(fd);
	return (1);
}

int	check_str(char *str, t_game *game, char *value)
{
	if (!ft_strncmp(str, "NO", 2) && game->textures.no_path == NULL)
		free(value);
	else if (!ft_strncmp(str, "SO", 2) && game->textures.so_path == NULL)
		free(value);
	else if (!ft_strncmp(str, "WE", 2) && game->textures.we_path == NULL)
		free(value);
	else if (!ft_strncmp(str, "EA", 2) && game->textures.ea_path == NULL)
		free(value);
	else if (!ft_strncmp(str, "C", 1) && game->textures.f == NULL)
		free(value);
	else if (!ft_strncmp(str, "F", 1) && game->textures.c == NULL)
		free(value);
	return (1);
}
