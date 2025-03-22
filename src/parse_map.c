#include "cub3d.h"

// Funkcja do usunięcia nowej linii na końcu stringa
char *trim_newline(char *str)
{
    int len = strlen(str);
    if (len > 0 && str[len - 1] == '\n')
        str[len - 1] = '\0';
    return str;
}

void parse_map(t_game *game, char *filename)
{
    int fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        perror("Error: Cannot open map file");
        exit(1);
    }

    char *line = NULL;
    size_t len = 0;
    FILE *file = fdopen(fd, "r");

    while (getline(&line, &len, file) != -1)
    {
        if (strncmp(line, "NO ", 3) == 0) game->no_texture = strdup(trim_newline(line + 3));
        else if (strncmp(line, "SO ", 3) == 0) game->so_texture = strdup(trim_newline(line + 3));
        else if (strncmp(line, "WE ", 3) == 0) game->we_texture = strdup(trim_newline(line + 3));
        else if (strncmp(line, "EA ", 3) == 0) game->ea_texture = strdup(trim_newline(line + 3));
    }
    
    free(line);
    fclose(file);
    close(fd);
}
