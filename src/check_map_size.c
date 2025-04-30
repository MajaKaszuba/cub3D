#include "../includes/cub3d.h"

void check_x_and_y(t_game *game, char *str){
	char *line;
	int         fd_sizes;
	int i;
	int temp;

	i = 0;
	fd_sizes = open(str, O_RDONLY);
	while (i < game->map.lines_tilmap){
		line = get_next_line(fd_sizes);
		i++;
		free(line);
	}
	line = get_next_line(fd_sizes);
	if (!line)
		printf("Error No Map");
	temp = ft_strlen(line) - 1;
	while(1){
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
