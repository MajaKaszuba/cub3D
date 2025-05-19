/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map_vals_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaszuba <mkaszuba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:24:21 by mkaszuba          #+#    #+#             */
/*   Updated: 2025/05/19 14:41:49 by mkaszuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	ft_isnumber(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	is_composed_with_coloric(t_game *game, char *str, char *str2, int c)
{
	size_t	len;
	int		i;

	len = ft_strlen(str);
	i = 0;
	while ((size_t)i < len)
	{
		if (str[i] != ',' && !ft_isnumber(str[i]))
			free_strings(game, str, str2, 0);
		i++;
	}
	if (c == 0)
		game->textures.c = str;
	else
		game->textures.f = str;
}

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

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

int	is_only_whitespace(t_game *game, const char *str, bool map_status)
{
	const char	*cpy;

	cpy = str;
	if (is_not_map_format(str) && map_status == true)
	{
		free((char *)str);
		free_strings(game, NULL, NULL, 2);
	}
	while (*str)
	{
		if (!ft_isspace(*str))
			return (0);
		str++;
	}
	str = cpy;
	if (map_status == true)
	{
		free((char *)str);
		free_strings(game, NULL, NULL, 2);
	}
	return (1);
}
