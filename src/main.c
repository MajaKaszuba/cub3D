#include "../includes/cub3d.h"

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
}

void start_texture(t_game *game)
{
    game->mlx = mlx_init();
    game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	game->img.img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bpp, &game->img.line_len, &game->img.endian);	

    load_textures(game);
    game->player.pa = 0;
}

static void load_texture(void *mlx, t_img *texture, char *path)
{
    texture->img = mlx_xpm_file_to_image(mlx, path, &texture->width, &texture->height);
    if (!texture->img)
    {
        printf("Error: Failed to load texture %s\n", path);
        exit(1);
    }
    texture->addr = mlx_get_data_addr(texture->img, &texture->bpp, &texture->line_len, &texture->endian);
    if (!texture->addr)
    {
        write(2, "Failed to get texture buffer\n", 30);
        return (1);
    }
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
    load_texture(game->mlx, &game->textures.NO, game->textures.no_path);
    if (!game->textures.NO.img) {
        printf("❌ Błąd: Nie udało się wczytać NO: %s\n", game->textures.no_path);
        exit(1);
    }

    printf("🔹 SO: %s\n", game->textures.so_path);
    load_texture(game->mlx, &game->textures.SO, game->textures.so_path);
    if (!game->textures.SO.img) {
        printf("❌ Błąd: Nie udało się wczytać SO: %s\n", game->textures.so_path);
        exit(1);
    }

    printf("🔹 WE: %s\n", game->textures.we_path);
    load_texture(game->mlx, &game->textures.WE, game->textures.we_path);
    if (!game->textures.WE.img) {
        printf("❌ Błąd: Nie udało się wczytać WE: %s\n", game->textures.we_path);
        exit(1);
    }

    printf("🔹 EA: %s\n", game->textures.ea_path);
    load_texture(game->mlx, &game->textures.EA, game->textures.ea_path);
    if (!game->textures.EA.img) {
        printf("❌ Błąd: Nie udało się wczytać EA: %s\n", game->textures.ea_path);
        exit(1);
    }

    printf("✅ Tekstury wczytane poprawnie!\n");
}

/*void print_char_array(char **array, int rows) {
    int i = 0;
    while (i < rows){
        printf("%s", array[i]);
        i++;
    }
}*/

void put_pixel(t_game *game, int x, int y, int color)
{
    if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
    {
        char *dst = game->img.addr + (y * game->img.line_len + x * (game->img.bpp / 8));
        *(unsigned int*)dst = color;
    }
}

unsigned int get_texture_color(t_img *texture, int x, int y)
{
    char *pixel;
    unsigned int color;

    // Check if the coordinates are within the bounds of the texture
    if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
        return (0); // Return 0 (black) if out of bounds

    // Calculate the pixel's memory address
    pixel = texture->addr + (y * texture->line_len + x * (texture->bpp / 8));
    // Read the color (assuming the texture is using 32-bit color)
    color = *(unsigned int *)pixel;

    return color;
}

void draw_vertical_line(t_game *game, int x, int height, int side) {
    int start = (WIN_HEIGHT / 2) - (height / 2);
    int end = (WIN_HEIGHT / 2) + (height / 2);
    if (start < 0)
        start = 0;
    if (end >= WIN_HEIGHT)
        end = WIN_HEIGHT - 1;

    t_img *texture;
    if (side == 0) texture = &game->textures.NO;
    else if (side == 1) texture = &game->textures.SO;
    else if (side == 2) texture = &game->textures.EA;
    else texture = &game->textures.WE; 
        
    float texture_step = (float)texture->height / height;
    float texture_pos = (start - (WIN_HEIGHT / 2) + (height / 2)) * texture_step;

    for (int y = 0; y < WIN_HEIGHT; y++) {
        if (y < start)
            put_pixel(game, x, y, 0x87CEEB); // Ceiling
        else if (y >= start && y < end) {
            int tex_y = (int)texture_pos & (texture->height - 1); // szybciej modulo jak height = potęga 2
            int tex_x = game->wall_hit_x * texture->width;        // tu poprawka!!
            if (tex_x < 0) tex_x = 0;
            if (tex_x >= texture->width) tex_x = texture->width - 1;

            unsigned int color = get_texture_color(texture, tex_x, tex_y);
            put_pixel(game, x, y, color);

            texture_pos += texture_step;
        } else {
            put_pixel(game, x, y, 0x228B22); // Floor
        }
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
        while (!hit)
        {
            ray_x += dx * 0.01;
            ray_y += dy * 0.01;
            if (game->map.valid_map[(int)ray_y][(int)ray_x] == '1')
            {
                hit = 1;
                if (fabsf(ray_x - floorf(ray_x)) < fabsf(ray_y - floorf(ray_y)))
                    game->wall_hit_x = ray_y - floorf(ray_y);
                else
                    game->wall_hit_x = ray_x - floorf(ray_x);
            }            
        }
        float distance = sqrtf((ray_x - game->player.px) * (ray_x - game->player.px) + 
                               (ray_y - game->player.py) * (ray_y - game->player.py)) * 
                               cos(ray_angle - game->player.pa);
        int line_height = (int)(WIN_HEIGHT / (distance + 0.0001));
        int side = 0; // Domyślnie północ
        if (dy < 0) {
            side = 1;  // Południe
        } else if (dx > 0) {
            side = 2;  // Wschód
        } else {
            side = 3;  // Zachód
        }

        draw_vertical_line(game, i, line_height, side);
        ray_angle += angle_step;
    }
}

int update(t_game *game)
{
    cast_rays(game);
    mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
    mlx_put_image_to_window(game->mlx, game->win, game->textures.NO.img, 0, 0);
    mlx_put_image_to_window(game->mlx, game->win, game->textures.SO.img, 0, 64);
    mlx_put_image_to_window(game->mlx, game->win, game->textures.WE.img, 0, 128);
    mlx_put_image_to_window(game->mlx, game->win, game->textures.EA.img, 0, 192);
    return 0;
}

void rotate_player(t_game *game, float direction)
{
    game->player.pa += direction * ROTATE_SPEED;
}

void move_player(t_game *game, float move_x, float move_y)
{
    float new_px = game->player.px + move_x * MOVE_SPEED;
    float new_py = game->player.py + move_y * MOVE_SPEED;
    float check_y;
    float check_x;

    if (move_x > 0)
        check_x = new_px + 0.1f;
    else
        check_x = new_px - 0.1f;
    if (game->map.valid_map[(int)game->player.py][(int)check_x] != '1')
        game->player.px = new_px;
    if (move_y > 0)
        check_y = new_py + 0.1f;
    else
        check_y = new_py - 0.1f;
    if (game->map.valid_map[(int)check_y][(int)game->player.px] != '1')
        game->player.py = new_py;
}

int key_press(int keycode, t_game *game)
{
    if (keycode == 65307) // ESC
        exit(0);
    if (keycode == 65361) // Left Arrow
        rotate_player(game, -1);
    else if (keycode == 65363) // Right Arrow
        rotate_player(game, 1);
    else if (keycode == 119) // W
        move_player(game, cos(game->player.pa), sin(game->player.pa));
    else if (keycode == 115) // S
        move_player(game, -cos(game->player.pa), -sin(game->player.pa));
    else if (keycode == 100) // A
        move_player(game, -sin(game->player.pa), cos(game->player.pa));
    else if (keycode == 97) // D
        move_player(game, sin(game->player.pa), -cos(game->player.pa));

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
    fill_map_vals(&game, argv[1]);
    printf("map val:%s", game.textures.no_path);
    start_texture(&game);
    check_x_and_y(&game, argv[1]);
    alloc_map(&game, argv[1]);
    color_convert(&game);
    map_check(&game);
    mlx_loop_hook(game.mlx, update, &game);
    mlx_hook(game.win, 2, 1L << 0, key_press, &game);
    mlx_loop(game.mlx);

    // printf("%s", game.textures.no_path);
    // for (int i = 0; i < game.map.highest_y; i++) {
    //     free(game.map.valid_map[i]);
    // }
    // free(game.map.valid_map);
    // free(game.textures.no_path);
    // free(game.textures.so_path);
    // free(game.textures.ea_path);
    // free(game.textures.we_path);
    // free(game.textures.F);
    // free(game.textures.C);
    return 0;
}