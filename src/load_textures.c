#include "../includes/cub3d.h"

static void load_texture(void *mlx, t_img *texture, char *path)
{
    texture->img = mlx_xpm_file_to_image(mlx, path, &texture->width, &texture->height);
    if (!texture->img)
    {
        printf("Error: Failed to load texture %s\n", path);
        exit(1);
    }
    texture->addr = mlx_get_data_addr(texture->img, &texture->bpp, &texture->line_len, &texture->endian);
}

void load_textures(t_game *game)
{
    printf("🔍 Wczytywanie tekstur...\n");

    if (!game->textures.no_path || !game->textures.so_path ||
        !game->textures.we_path || !game->textures.ea_path) 
    {
        printf("❌ Błąd: Brak ścieżki do tekstury!\n");
        exit(1);
    }

    printf("🔹 NO: %s\n", game->textures.no_path);
    game->textures.NO.img = mlx_xpm_file_to_image(game->mlx, game->textures.no_path, &game->textures.NO.width, &game->textures.NO.height);
    if (!game->textures.NO.img) {
        printf("❌ Błąd: Nie udało się wczytać NO: %s\n", game->textures.no_path);
        exit(1);
    }

    printf("🔹 SO: %s\n", game->textures.so_path);
    game->textures.SO.img = mlx_xpm_file_to_image(game->mlx, game->textures.so_path, &game->textures.SO.width, &game->textures.SO.height);
    if (!game->textures.SO.img) {
        printf("❌ Błąd: Nie udało się wczytać SO: %s\n", game->textures.so_path);
        exit(1);
    }

    printf("🔹 WE: %s\n", game->textures.we_path);
    game->textures.WE.img = mlx_xpm_file_to_image(game->mlx, game->textures.we_path, &game->textures.WE.width, &game->textures.WE.height);
    if (!game->textures.WE.img) {
        printf("❌ Błąd: Nie udało się wczytać WE: %s\n", game->textures.we_path);
        exit(1);
    }

    printf("🔹 EA: %s\n", game->textures.ea_path);
    game->textures.EA.img = mlx_xpm_file_to_image(game->mlx, game->textures.ea_path, &game->textures.EA.width, &game->textures.EA.height);
    if (!game->textures.EA.img) {
        printf("❌ Błąd: Nie udało się wczytać EA: %s\n", game->textures.ea_path);
        exit(1);
    }

    printf("✅ Tekstury wczytane poprawnie!\n");
}

unsigned int get_texture_color(t_img *texture, int x, int y)
{
    char    *pixel;
    int     color;

    if (!texture->addr || x < 0 || y < 0 || x >= texture->width || y >= texture->height)
        return (0); // Zwracamy czarny kolor jeśli błąd

    pixel = texture->addr + (y * texture->line_len + x * (texture->bpp / 8));
    color = *(unsigned int *)pixel;
    return (color);
}
