#include "cub3d.h"

void    init_window(t_game *game)
{
    // Inicjalizacja MinilibX
    game->mlx = mlx_init();
    if (!game->mlx)
    {
        perror("Error: mlx_init() failed");
        exit(1);
    }
    printf("MLX initialized successfully\n");

    // Tworzymy okno
    game->win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D");
    if (!game->win)
    {
        ft_putstr_fd("Error: mlx_new_window() failed\n", 2);
        exit(1);
    }

    // Załadowanie tekstur z obsługą błędów
    printf("Loading texture: %s\n", game->no_texture);
    game->no_img = mlx_xpm_file_to_image(game->mlx, game->no_texture, &game->tex_width, &game->tex_height);
    game->so_img = mlx_xpm_file_to_image(game->mlx, game->so_texture, &game->tex_width, &game->tex_height);
    game->we_img = mlx_xpm_file_to_image(game->mlx, game->we_texture, &game->tex_width, &game->tex_height);
    game->ea_img = mlx_xpm_file_to_image(game->mlx, game->ea_texture, &game->tex_width, &game->tex_height);
    if (!game->no_img || !game->so_img || !game->we_img || !game->ea_img)
    {
        perror("Error: Unable to load texture file");
        exit(1);
    }
}

void    render_scene(t_game *game)
{
    // Tutaj będzie raycasting - na razie pusty ekran
    mlx_pixel_put(game->mlx, game->win, 10, 10, 0xFFFFFF);
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage: ./cub3D <map.cub>\n");
        return (1);
    }

    t_game game;
    parse_map(&game, argv[1]);  // 🔹 Wczytaj mapę i przypisz ścieżki tekstur

    // Debugowanie
    printf("NO Texture Path: %s\n", game.no_texture);
    printf("SO Texture Path: %s\n", game.so_texture);
    printf("WE Texture Path: %s\n", game.we_texture);
    printf("EA Texture Path: %s\n", game.ea_texture);

    init_window(&game);
    render_scene(&game);
    mlx_loop(game.mlx);

    return 0;
}
