#include "../includes/cub3d.h"


char *ft_strcpy(char *dst, const char *src) {
    int i = 0;
	int j = 0;
	while (src[i] == 32)
		i++;
    while (src[i] != '\0') {
        dst[j] = src[i]; 
        i++;
		j++;
    }
    dst[j] = '\0';
    return dst;
}

bool check_for_all(t_game *game)
{
	if (game->textures.no_path != NULL && game->textures.we_path != NULL && game->textures.so_path != NULL &&
		game->textures.ea_path != NULL && game->textures.F != NULL && game->textures.C != NULL)
		return (true);
	return (false);
}

void find_id(char *str, t_game *game)
{
    char *value;

    printf("Odczytana linia: '%s'\n", str); // 🟢 DEBUG

    // Znajdź pierwszą spację i przejdź do wartości
    value = ft_strchr(str, ' ');
    if (!value || !*(value + 1))
    {
        printf("Error: Brak wartości dla identyfikatora -> %s\n", str);
        return;
    }
    value = ft_strtrim(value + 1, " \n"); // Usunięcie spacji i nowej linii

    if (!value)
    {
        printf("Error: ft_strtrim() zwrócił NULL\n");
        return;
    }

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
    {
        printf("Error: Nieznany identyfikator -> %s\n", str);
        free(value);
    }

    printf("Przypisano: %s -> '%s'\n", str, value); // 🟢 DEBUG
}

bool is_map_part(t_game *game, char *str){
	int i = 0;
	if(str[0] == '\n')
			return false;
	i = 0;
	while (str[i]){
		if (str[i] == ' ' || str[i] == '1'){
			i++;
		}
		else
			break ;
	}
	if ((ft_strlen(str) - 1 == i) && check_for_all(game)){
		printf("returned true\n");
		return true;
	}
	return false;
}

int ft_isspace(char c) {
    return (c == ' '  || c == '\t' || c == '\n' || 
            c == '\v' || c == '\f' || c == '\r');
}
bool is_not_map_format(char *str){
	size_t len;
	int i;

	i = 0;
	len = ft_strlen(str);
	while (str[i] == ' ' || str[i] == '0' || str[i] == '1' || str[i] == 'N' 
			|| str[i] == 'S' || str[i] == 'W' || str[i] == 'E' || str[i] == '\n')
			i++;
	if (i != len){
		return (1);
	}
	return(0);
}


int is_only_whitespace(const char *str, bool map_status) {

	if (is_not_map_format(str) && map_status == true){
		printf("Wrong Format inside map part\n");
		printf("End Program");
	}
    while (*str) {
        if (!ft_isspace(*str)) {
            return 0; 
        }
        str++;
    }
	if (map_status == true){
		printf("white line in map");
	}
    return 1;
}


void fill_map_vals(t_game *game, char *str)
{
	char *line;
	int         fd_vals;
	bool map_started;
	
	map_started = false;
	fd_vals = open(str, O_RDONLY);
	while(1){
		line = get_next_line(fd_vals);
		if (map_started == false)
			game->map.lines_tilmap += 1;
		if (!line)
			break;
		if (is_only_whitespace(line, map_started))
			continue;
		if (map_started == false && is_map_part(game, line)) {
            map_started = true;
            free(line);
            continue;
        }
		if (!map_started)
			find_id(line, game);
		free(line);
	}
	close(fd_vals);
}