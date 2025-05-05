/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map_vals_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaszuba <mkaszuba@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:24:21 by mkaszuba          #+#    #+#             */
/*   Updated: 2025/05/05 16:08:43 by mkaszuba         ###   ########.fr       */
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

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
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
