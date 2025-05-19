/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map_vals_logic.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaszuba <mkaszuba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:24:21 by mkaszuba          #+#    #+#             */
/*   Updated: 2025/05/19 15:25:15 by mkaszuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	check_for_all(t_game *game)
{
	if (game->textures.no_path != NULL && game->textures.we_path != NULL
		&& game->textures.so_path != NULL
		&& game->textures.ea_path != NULL && game->textures.f != NULL
		&& game->textures.c != NULL)
		return (true);
	return (false);
}

void	find_id(char *str, t_game *game)
{
	char	*value;

	value = ft_strchr(str, ' ');
	if (!value || !*(value + 1))
		return (free_strings(game, str, value, 0));
	value = ft_strtrim(value + 1, " \n");
	if (!value)
		return ((void)printf("Error: ft_strtrim() zwrócił NULL\n"));
	if (!ft_strncmp(str, "NO", 2) && game->textures.no_path == NULL)
		game->textures.no_path = value;
	else if (!ft_strncmp(str, "SO", 2) && game->textures.so_path == NULL)
		game->textures.so_path = value;
	else if (!ft_strncmp(str, "WE", 2) && game->textures.we_path == NULL)
		game->textures.we_path = value;
	else if (!ft_strncmp(str, "EA", 2) && game->textures.ea_path == NULL)
		game->textures.ea_path = value;
	else if (!ft_strncmp(str, "C", 1) && game->textures.c == NULL)
		is_composed_with_coloric(game, value, str, 0);
	else if (!ft_strncmp(str, "F", 1) && game->textures.f == NULL)
		is_composed_with_coloric(game, value, str, 1);
	else if (check_str(str, game, value))
		return ;
	else
		return (free_strings(game, str, value, 0));
}

bool	is_map_part(t_game *game, char *str)
{
	int	i;

	if (str[0] == '\n')
		return (false);
	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '1')
			i++;
		else
			break ;
	}
	if ((ft_strlen(str) - 1 == (size_t)i) && check_for_all(game))
	{
		printf("returned true\n");
		return (true);
	}
	return (false);
}

bool	is_not_map_format(const char *str)
{
	size_t	len;
	int		i;

	i = 0;
	len = ft_strlen(str);
	while (str[i] == ' ' || str[i] == '0' || str[i] == '1' || str[i] == 'N'
		|| str[i] == 'S' || str[i] == 'W' || str[i] == 'E' || str[i] == '\n')
		i++;
	if ((size_t)i != len)
		return (1);
	return (0);
}

void	fill_map_vals(t_game *game, char *str)
{
	char	*line;
	int		fd_vals;
	bool	map_started;

	map_started = false;
	fd_vals = open(str, O_RDONLY);
	line = get_next_line(fd_vals);
	while (line)
	{
		if (!map_started)
			game->map.lines_tilmap++;
		if (is_only_whitespace(game, line, map_started))
			;
		else if (!map_started && is_map_part(game, line))
		{
			map_started = true;
			game->map.lines_tilmap--;
		}
		else if (!map_started)
			find_id(line, game);
		free(line);
		line = get_next_line(fd_vals);
	}
	close(fd_vals);
}
