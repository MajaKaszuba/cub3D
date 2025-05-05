/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map_vals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaszuba <mkaszuba@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:24:21 by mkaszuba          #+#    #+#             */
/*   Updated: 2025/05/05 15:31:23 by mkaszuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*ft_strcpy(char *dst, const char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (src[i] == 32)
		i++;
	while (src[i] != '\0')
	{
		dst[j] = src[i];
		i++;
		j++;
	}
	dst[j] = '\0';
	return (dst);
}

bool	check_for_all(t_game *game)
{
	if (game->textures.no_path != NULL && game->textures.we_path != NULL
		&& game->textures.so_path != NULL
		&& game->textures.ea_path != NULL && game->textures.F != NULL
		&& game->textures.C != NULL)
		return (true);
	return (false);
}

void	find_id(char *str, t_game *game)
{
	char	*value;

	value = ft_strchr(str, ' ');
	if (!value || !*(value + 1))
		return ((void)printf(
				"Error: Brak wartości dla identyfikatora -> %s\n", str));
	value = ft_strtrim(value + 1, " \n");
	if (!value)
		return ((void)printf("Error: ft_strtrim() zwrócił NULL\n"));
	if (!ft_strncmp(str, "NO", 2))
		game->textures.no_path = value;
	else if (!ft_strncmp(str, "SO", 2))
		game->textures.so_path = value;
	else if (!ft_strncmp(str, "WE", 2))
		game->textures.we_path = value;
	else if (!ft_strncmp(str, "EA", 2))
		game->textures.ea_path = value;
	else if (!ft_strncmp(str, "C", 1))
		game->textures.C = value;
	else if (!ft_strncmp(str, "F", 1))
		game->textures.F = value;
	else
		return ((void)(printf("Error: Nieznany identyfikator -> %s\n", str),
			free(value)));
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

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
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

int	is_only_whitespace(const char *str, bool map_status)
{
	if (is_not_map_format(str) && map_status == true)
	{
		printf("Wrong Format inside map part\n");
		printf("End Program");
	}
	while (*str)
	{
		if (!ft_isspace(*str))
			return (0);
		str++;
	}
	if (map_status == true)
		printf("white line in map");
	return (1);
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
		if (is_only_whitespace(line, map_started))
			;
		else if (!map_started && is_map_part(game, line))
			map_started = true;
		else if (!map_started)
			find_id(line, game);
		free(line);
		line = get_next_line(fd_vals);
	}
	close(fd_vals);
}
