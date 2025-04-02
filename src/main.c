#include "../includes/cub3d.h"

void free_textures(t_game *game)
{
    if (game->textures.NO.img) mlx_destroy_image(game->mlx, game->textures.NO.img);
    if (game->textures.SO.img) mlx_destroy_image(game->mlx, game->textures.SO.img);
    if (game->textures.WE.img) mlx_destroy_image(game->mlx, game->textures.WE.img);
    if (game->textures.EA.img) mlx_destroy_image(game->mlx, game->textures.EA.img);
}

void start_game(t_game *game)
{
    game->textures.no_path = NULL;
    game->textures.so_path = NULL;
    game->textures.we_path = NULL;
    game->textures.ea_path = NULL;
    game->textures.F = NULL;
    game->textures.C = NULL;
    game->map.highest_x = 0;
    game->map.highest_y = 0;
    game->map.lines_tilmap = -1;
    game->player.is_player = 0;
}

// void start_texture(t_game *game)
// {
//     game->mlx = mlx_init();
//     game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
// 	game->img.img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
// 	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bpp, &game->img.line_len, &game->img.endian);	

//     load_textures(game);

//     game->player.px = 3;
//     game->player.py = 3;
//     game->player.pa = 0;
// }

void put_pixel(t_game *game, int x, int y, int color)
{
    if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
    {
        char *dst = game->img.addr + (y * game->img.line_len + x * (game->img.bpp / 8));
        *(unsigned int*)dst = color;
    }
}

void draw_vertical_line(t_game *game, int x, int height, t_img *texture, float tex_pos)
{
    int start = (WIN_HEIGHT / 2) - (height / 2);
    int end = (WIN_HEIGHT / 2) + (height / 2);

    for (int y = 0; y < WIN_HEIGHT; y++)
    {
        if (y < start)
            put_pixel(game, x, y, 0x87CEEB); // Sufit
        else if (y >= start && y < end)
        {
            int tex_y = (int)(tex_pos) % texture->height;
            unsigned int color = get_texture_color(texture, x % texture->width, tex_y);
            put_pixel(game, x, y, color);
        }
        else
            put_pixel(game, x, y, 0x228B22); // Podłoga
    }
}

void cast_rays(t_game *game)
{
    float ray_angle = game->player.pa - (FOV / 2);
    float angle_step = FOV / NUM_RAYS;

    for (int i = 0; i < NUM_RAYS; i++)
    {
        float ray_x = game->player.px;
        float ray_y = game->player.py;
        float dx = cos(ray_angle);
        float dy = sin(ray_angle);
        int hit = 0;
        t_img *texture = NULL;

        while (!hit)
        {
            ray_x += dx * 0.01;
            ray_y += dy * 0.01;
            if (game->map.valid_map[(int)ray_y][(int)ray_x] == '1')
            {
                hit = 1;
                if (fabs(dx) > fabs(dy))
                    texture = (dx > 0) ? &game->textures.EA : &game->textures.WE;
                else
                    texture = (dy > 0) ? &game->textures.SO : &game->textures.NO;
            }
        }

        float distance = sqrtf((ray_x - game->player.px) * (ray_x - game->player.px) + 
                               (ray_y - game->player.py) * (ray_y - game->player.py)) * 
                               cos(ray_angle - game->player.pa);
        int line_height = (int)(WIN_HEIGHT / (distance + 0.0001));
        draw_vertical_line(game, i, line_height, texture, ray_y * texture->height);
        ray_angle += angle_step;
    }
}

int update(t_game *game)
{
    cast_rays(game);
    mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
    return 0;
}

int key_press(int keycode, t_game *game)
{
    if (keycode == 65307) // ESC
        exit(0);
    if (keycode == 97) // A - obrót w lewo
        game->player.pa -= ROTATE_SPEED;
    if (keycode == 100) // D - obrót w prawo
        game->player.pa += ROTATE_SPEED;
    if (keycode == 119) // W - ruch do przodu
    {
        game->player.px += cos(game->player.pa) * MOVE_SPEED;
        game->player.py += sin(game->player.pa) * MOVE_SPEED;
    }
    if (keycode == 115) // S - ruch do tyłu
    {
        game->player.px -= cos(game->player.pa) * MOVE_SPEED;
        game->player.py -= sin(game->player.pa) * MOVE_SPEED;
    }
    return 0;
}

int main(int argc, char **argv)
{
    t_game game;

    if (argc != 2)
    {
        printf("Error: Valid input: ./cub3d map_name.cub\n");
        return (0);
    }
    check_args(argv[1]);
    start_game(&game);
    fill_map_vals(&game, argv[1]);

    //w te funkcje nie wchodzi!!!
    check_x_and_y(&game, argv[1]);
    alloc_map(&game, argv[1]);
    color_convert(&game);
    map_check(&game);

   // mlx_loop_hook(game.mlx, update, &game);
    //mlx_hook(game.win, 2, 1L << 0, key_press, &game);
    //mlx_loop(game.mlx);

    //free_textures(&game);

    for (int i = 0; i < game.map.highest_y; i++)
        free(game.map.valid_map[i]);
    free(game.map.valid_map);

    return (0);
}
