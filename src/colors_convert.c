#include "../includes/cub3d.h"

int *convert(char *str)
{
	char arr[3][4];
	int i = 0;
	int k = 0;
	int size = ft_strlen(str);
	while (i < 3)
	{
		int j = 0;
		while (j < 3){
			if (k >= size)
				break;
			if(str[k] != ',')
					arr[i][j] = str[k];
			else{
				k++;
				break;
			}
			j++;
			k++;
		}
		if (k < size)
			if (str[k] == ',')
				k++;
		arr[i][j] = '\0';
		i++;
	}
	printf("%s\n", arr[1]);
	return((ft_atoi(arr[0]) << 16) | (ft_atoi(arr[1]) << 8) | ft_atoi(arr[2]));
}

void color_convert(t_game *game)
{
	game->textures.floor_color = convert(game->textures.F);
	game->textures.ceeling_color = convert(game->textures.C);
	printf("Color in hex: 0x%X\n", game->textures.floor_color);
	printf("Color in hex: 0x%X\n", game->textures.ceeling_color);
}