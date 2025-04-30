#include "../includes/cub3d.h"

/*
	directions
	0 - starting point (sends everywhere)
	1 - signal from left
	2 - signal from right
	3 - signal from top
	4 - singal from bottom
*/

bool is_player_value(char c){
	if (c == 'S' || c == 'W' || c == 'N' || c == 'E')
		return (0);
	return (1);
}


bool x_check(t_game *game, int x, int y){
	game->map.valid_map[y][x] = 'x';
	//warunki lewo
	if (x > 0){
		if (game->map.valid_map[y][x -1] == 'X')
			x_check(game, x - 1, y);
		else if (game->map.valid_map[y][x - 1] == is_player_value(game->map.valid_map[y][x - 1]))
			printf("Player out of map\n");
		else if (game->map.valid_map[y][x - 1] == '0')
			printf("Fatal Error\n");
	}
	//warunki prawo
	if (x < game->map.highest_x - 1){
		if (game->map.valid_map[y][x + 1] == 'X'){
			x_check(game, x + 1, y);
		}
		else if (game->map.valid_map[y][x + 1] == 'P')
			printf("Player out of map\n");
		else if (game->map.valid_map[y][x + 1] == '0')
			printf("Fatal Error\n");
	}
	//warunki gora 
	if (y > 0){
		if (game->map.valid_map[y - 1][x] == 'X')
			x_check(game, x, y - 1);
		else if (game->map.valid_map[y - 1][x] == 'P')
			printf("Player out of map\n");
		else if (game->map.valid_map[y - 1][x] == '0')
			printf("Fatal Error\n");
	}
	//warunki dol
	if (y < game->map.highest_y - 1){
		if (game->map.valid_map[y + 1][x] == 'X')
			x_check(game, x, y + 1);
		else if (game->map.valid_map[y + 1][x] == 'P')
			printf("Player out of map\n");
		else if (game->map.valid_map[y + 1][x] == '0')
			printf("Fatal Error\n");
	}
	return (1);
}

bool zero_flood_check(t_game *game, int j, int i){ // j = x  i = y

	game->map.valid_map[i][j] = 'O';
	//warunki lewo
	if (game->map.valid_map[i][j -1] == '0')
		zero_flood_check(game, j - 1, i);
	else if (game->map.valid_map[i][j - 1] == 'X')
		printf("Fatal Error\n");
	//warunki prawo
	if (game->map.valid_map[i][j + 1] == '0')
		zero_flood_check(game, j + 1, i);
	else if (game->map.valid_map[i][j + 1] == 'X')
		printf("Fatal Error\n");
	//warunki gora 
	if (game->map.valid_map[i - 1][j] == '0')
		zero_flood_check(game, j, i - 1);
	else if (game->map.valid_map[i - 1][j] == 'X')
		printf("Fatal Error\n");
	//warunki dol
	if (game->map.valid_map[i + 1][j] == '0')
		zero_flood_check(game, j, i + 1);
	else if (game->map.valid_map[i + 1][j] == 'X')
		printf("Fatal Error\n");
	return (1);

}

bool player_in_map(t_game *game, int pos_x, int pos_y){
	if (game->map.valid_map[pos_y][pos_x - 1] == 'X')
		printf("Fatal Error\n");
	//warunki prawo
	if (game->map.valid_map[pos_y][pos_x + 1] == 'X')
		printf("Fatal Error\n");
	if (game->map.valid_map[pos_y - 1][pos_x] == 'X')
		printf("Fatal Error\n");
	//warunki dol
	if (game->map.valid_map[pos_y + 1][pos_x] == 'X')
		printf("Fatal Error\n");
	return (1);
}

void zero_check(t_game *game){
	int i;
	int j;

	i = 1;
	while (i < game->map.highest_y - 1)
	{
		j = 1;
		while (j < game->map.highest_x - 1){
			if (game->map.valid_map[i][j] == '0')
				zero_flood_check(game, j, i);
			if (!is_player_value(game->map.valid_map[i][j])){
				player_in_map(game,j, i);
				game->player.is_player++;
				game->player.px = (float)j;
				game->player.py = (float)i;
				printf("%i | %i\n", (int)game->player.px, (int)game->player.py);
			}
			if (game->player.is_player > 1)
				printf("amount of players is more than 1");
			j++;
		}
		i++;
	}
}

void check_boundaries_x(t_game *game){
	int i;

	i = 0;
	while (i< game->map.highest_x)
	{
		if (game->map.valid_map[0][i] == '0')
			printf("error");
		else if (game->map.valid_map[0][i] == 'X')
			x_check(game, i, 0);
		i++;
	}
	i = 0;
	while (i< game->map.highest_x)
	{
		if (game->map.valid_map[game->map.highest_y - 1][i] == '0')
			printf("error");
		else if (game->map.valid_map[game->map.highest_y -1][i] == 'X')
			x_check(game, i ,game->map.highest_y - 1);
		i++;
	}
}	

void check_boundaries_y(t_game *game){
	int i;

	i = 0;
	while (i < game->map.highest_y)
	{
		if (game->map.valid_map[i][0] == '0')
			printf("error");
		else if (game->map.valid_map[i][0] == 'X')
			x_check(game, 0, i);
		i++;
	}
	i = 0;
	while (i < game->map.highest_y)
	{
		if (game->map.valid_map[i][game->map.highest_x - 1] == '0')
			printf("error %i | %i\n", i, game->map.highest_x - 1);
		else if (game->map.valid_map[i][game->map.highest_x - 1] == 'X')
			x_check(game, game->map.highest_x - 1, i);
		i++;
	}
}

void map_check(t_game *game){

	check_boundaries_x(game);
	check_boundaries_y(game);
	zero_check(game);
	int i = 0;
	
	while (i < game->map.highest_y){
        printf("%s\n", game->map.valid_map[i]);
        i++;
    }
}