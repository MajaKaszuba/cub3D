/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_convert.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaszuba <mkaszuba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:17:01 by mkaszuba          #+#    #+#             */
/*   Updated: 2025/05/19 14:41:08 by mkaszuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	convert(char *str)
{
	char	arr[3][4];
	int		i;
	int		j;
	int		k;
	int		size;

	i = 0;
	k = 0;
	size = ft_strlen(str);
	while (i < 3)
	{
		j = 0;
		while (k < size && str[k] != ',' && j < 3)
			arr[i][j++] = str[k++];
		arr[i][j] = '\0';
		if (str[k] == ',')
			k++;
		i++;
	}
	return ((ft_atoi(arr[0]) << 16) | (ft_atoi(arr[1]) << 8) | ft_atoi(arr[2]));
}

void	color_convert(t_game *game)
{
	game->textures.floor_color = convert(game->textures.f);
	game->textures.ceeling_color = convert(game->textures.c);
}
