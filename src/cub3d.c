#include "cub3d.h"

void    init_window(t_game *game)
{
    // Inicjalizacja MinilibX
    game->mlx = mlx_init();
    if (!game->mlx)
    {
        ft_putstr_fd("Error: mlx_init failed\n", 2);
        exit(1);
    }

    // Tworzymy okno
    game->win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D");
    if (!game->win)
    {
        ft_putstr_fd("Error: mlx_new_window failed\n", 2);
        exit(1);
    }

    // Załadowanie tekstur
    game->no_img = mlx_xpm_file_to_image(game->mlx, game->no_texture, &game->tex_width, &game->tex_height);
    game->so_img = mlx_xpm_file_to_image(game->mlx, game->so_texture, &game->tex_width, &game->tex_height);
    game->we_img = mlx_xpm_file_to_image(game->mlx, game->we_texture, &game->tex_width, &game->tex_height);
    game->ea_img = mlx_xpm_file_to_image(game->mlx, game->ea_texture, &game->tex_width, &game->tex_height);

    if (!game->no_img || !game->so_img || !game->we_img || !game->ea_img)
    {
        ft_putstr_fd("Error: Unable to load textures\n", 2);
        exit(1);
    }
}

void    render_scene(t_game *game)
{
    // Tutaj będziesz wywoływał funkcję raycastingu
    // Która rysuje ściany, tekstury i inne elementy

    // Przykładowe rysowanie pikseli (można to zastąpić raycastingiem)
    mlx_pixel_put(game->mlx, game->win, 10, 10, 0xFFFFFF); // Przykładowy piksel

    // Oczywiście, po zaimplementowaniu raycastingu, to będzie rysować ściany.
    // Renderowanie tekstur zależy od promieni rzucanych przez gracza.
}

int main(void)
{
    t_game game;

    // Inicjalizuj grę, okno, tekstury itd.
    init_window(&game);

    // Renderowanie sceny (tutaj trzeba dodać funkcję raycastingu)
    render_scene(&game);

    // Pętla główna, która trzyma okno otwarte
    mlx_loop(game.mlx);

    return 0;
}
