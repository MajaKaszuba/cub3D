#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>    // printf(), perror()
# include <stdlib.h>   // malloc(), free(), exit()
# include <unistd.h>   // read(), write(), close()
# include <fcntl.h>    // open()
# include <math.h>     // funkcje matematyczne (np. sqrt(), sin(), cos())
# include <string.h>   // manipulacja napisami (strchr(), strcmp())
# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"

# define SCREEN_WIDTH 800
# define SCREEN_HEIGHT 600

// Struktura gry
typedef struct s_game
{
    void    *mlx;         // wskaźnik do kontekstu MinilibX
    void    *win;         // wskaźnik do okna MinilibX
    char    *no_texture;  // tekstura północy
    char    *so_texture;  // tekstura południa
    char    *we_texture;  // tekstura zachodu
    char    *ea_texture;  // tekstura wschodu
    void    *no_img;      // obraz północnej tekstury
    void    *so_img;      // obraz południowej tekstury
    void    *we_img;      // obraz zachodniej tekstury
    void    *ea_img;      // obraz wschodniej tekstury
    int     tex_width;    // szerokość tekstur
    int     tex_height;   // wysokość tekstur
} t_game;

// Funkcje
void    init_window(t_game *game);
void    render_scene(t_game *game);

#endif
