#include "../includes/cub3d.h"

void load_textures(t_game *game) {
    printf("%s", game->textures.no_path);
    game->textures.NO.img = mlx_xpm_file_to_image(game->mlx, game->textures.no_path, &game->img.width, &game->img.height);
    if (!game->textures.NO.img) {
        printf("Error: Failed to load texture %s\n", game->textures.no_path);
        exit(1);
    }
    game->textures.SO.img = mlx_xpm_file_to_image(game->mlx, game->textures.so_path, &game->img.width, &game->img.height);
    if (!game->textures.SO.img) {
        printf("Error: Failed to load texture %s\n", game->textures.so_path);
        exit(1);
    }
    game->textures.WE.img = mlx_xpm_file_to_image(game->mlx, game->textures.we_path, &game->img.width, &game->img.height);
    if (!game->textures.WE.img) {
        printf("Error: Failed to load texture %s\n", game->textures.we_path);
        exit(1);
    }
    game->textures.EA.img = mlx_xpm_file_to_image(game->mlx, game->textures.ea_path, &game->img.width, &game->img.height);
    if (!game->textures.EA.img) {
        printf("Error: Failed to load texture %s\n", game->textures.ea_path);
        exit(1);
    }
}

void start_game(t_game *game){
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

    load_textures(game);
}
    
void start_texture(t_game *game)
{
    game->mlx = mlx_init();
    game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
    game->img.img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
    game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bpp, &game->img.line_len, &game->img.endian);	

    game->player.pa = 0;
}

void put_pixel(t_game *game, int x, int y, int color)
{
    if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
    {
        char *dst = game->img.addr + (y * game->img.line_len + x * (game->img.bpp / 8));
        *(unsigned int*)dst = color;
    }
}

unsigned int get_texture_color(t_img *texture, int x, int y) {
    if (x < 0 || y < 0 || x >= texture->width || y >= texture->height)
        return 0;  // Zwróć czarny kolor, jeśli współrzędne są poza granicami
    char *pixel = texture->addr + (y * texture->line_len + x * (texture->bpp / 8));
    return *(unsigned int *)pixel;
}

void draw_vertical_line(t_game *game, int x, int height, int side) {
    int start = (WIN_HEIGHT / 2) - (height / 2);
    int end = (WIN_HEIGHT / 2) + (height / 2);
    float texture_step = (float)game->textures.NO.height / height;
    float texture_pos = 0;
    t_img *texture;

    // Select texture based on ray side
    if (side == 0) {
        texture = &game->textures.NO;
    } else if (side == 1) {
        texture = &game->textures.SO;
    } else if (side == 2) {
        texture = &game->textures.EA;
    } else {
        texture = &game->textures.WE;
    }

    for (int y = 0; y < WIN_HEIGHT; y++) {
        if (y < start)
            put_pixel(game, x, y, 0x87CEEB); // Ceiling
        else if (y >= start && y < end) {
            int tex_y = (int)texture_pos;
            unsigned int color = get_texture_color(texture, 0, tex_y);
            put_pixel(game, x, y, color);
            texture_pos += texture_step;
        } else {
            put_pixel(game, x, y, 0x228B22); // Floor
        }
    }
}

void cast_rays(t_game *game) {
    float ray_angle = game->player.pa - (FOV / 2);
    float angle_step = FOV / NUM_RAYS;

    for (int i = 0; i < NUM_RAYS; i++) {
        float ray_x = game->player.px;
        float ray_y = game->player.py;
        float dx = cos(ray_angle);
        float dy = sin(ray_angle);
        int hit = 0;

        while (!hit) {
            ray_x += dx * 0.001;
            ray_y += dy * 0.001;

            if (game->map.valid_map[(int)ray_y][(int)ray_x] == '1') {
                hit = 1;
            }
        }

        float distance = sqrtf((ray_x - game->player.px) * (ray_x - game->player.px) + 
                               (ray_y - game->player.py) * (ray_y - game->player.py)) * 
                               cos(ray_angle - game->player.pa);
        int line_height = (int)(WIN_HEIGHT / (distance + 0.0001));

        // Określenie, która tekstura będzie używana
        int side = 0; // Domyślnie północ
        if (dy < 0) {
            side = 1;  // Południe
        } else if (dx > 0) {
            side = 2;  // Wschód
        } else {
            side = 3;  // Zachód
        }

        // Rysowanie ściany z teksturą
        draw_vertical_line(game, i, line_height, side);
        ray_angle += angle_step;
    }
}

int update(t_game *game)
{
    printf("update");
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
    // Calculate potential new positions
    float new_x = game->player.px + cos(game->player.pa) * MOVE_SPEED;
    float new_y = game->player.py + sin(game->player.pa) * MOVE_SPEED;

    // Check horizontal movement (along the x axis)
    if ((int)new_x >= 0 && (int)new_x < game->map.highest_x && (int)new_y >= 0 && (int)new_y < game->map.highest_y)
    {
        if (game->map.valid_map[(int)new_y][(int)new_x] != '1' || !is_player_value(game->map.valid_map[(int)new_y][(int)new_x])){
                    game->player.px = new_x;
        }
    }
    }
    if (keycode == 115) // S - ruch do tyłu
    {
        game->player.px -= cos(game->player.pa) * MOVE_SPEED;
        game->player.py -= sin(game->player.pa) * MOVE_SPEED;
    }
    return 0;
}

int main(int argc, char **argv){
    t_game game;

    if (argc != 2){
        printf("Error: Valid input: ./cub3d map_name.cub");
        return (0);
    }
    check_args(argv[1]);
    start_game(&game);
    write(1, "aa\n", 4);
    fill_map_vals(&game, argv[1]);
    start_texture(&game);
    check_x_and_y(&game, argv[1]);
    alloc_map(&game, argv[1]);
    color_convert(&game);
    map_check(&game);
    printf("map val:%c", game.map.valid_map[12][25]);
    mlx_loop_hook(game.mlx, update, &game);
    mlx_hook(game.win, 2, 1L << 0, key_press, &game);
    mlx_loop(game.mlx);

    printf("%s", game.textures.no_path);
    for (int i = 0; i < game.map.highest_y; i++) {
        free(game.map.valid_map[i]);
    }
    free(game.map.valid_map);
    free(game.textures.no_path);
    free(game.textures.so_path);
    free(game.textures.ea_path);
    free(game.textures.we_path);
    free(game.textures.F);
    free(game.textures.C);
    return 0;
}
