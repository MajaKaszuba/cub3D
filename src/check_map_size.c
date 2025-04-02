#include "../includes/cub3d.h"

void check_x_and_y(t_game *game, char *str)
{
	char *line;
	int fd_sizes;
	int i;
	int temp;

	i = 0;
	game->map.highest_x = 0;
	game->map.highest_y = 0;

	// Otwarcie pliku + obsługa błędu
	fd_sizes = open(str, O_RDONLY);
	if (fd_sizes < 0)
	{
		printf("Error: Could not open file %s\n", str);
		exit(EXIT_FAILURE);
	}

	// Pomijanie linii przed mapą
	while (i < game->map.lines_tilmap)
	{
		line = get_next_line(fd_sizes);
		if (!line)
		{
			printf("Error: Unexpected end of file before map\n");
			close(fd_sizes);
			exit(EXIT_FAILURE);
		}
		free(line);
		i++;
	}

	// Odczyt mapy
	while ((line = get_next_line(fd_sizes)) != NULL)
	{
		game->map.highest_y++;

		temp = ft_strlen(line);
		if (line[temp - 1] == '\n')
    		temp--;
		if (temp > game->map.highest_x)
			game->map.highest_x = temp;

		free(line);
	}

	close(fd_sizes);

	// Sprawdzenie, czy mapa w ogóle istniała
	if (game->map.highest_y == 0 || game->map.highest_x == 0)
	{
		printf("Error: No valid map found in file %s\n", str);
		exit(EXIT_FAILURE);
	}
}
