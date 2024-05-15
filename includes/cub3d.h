#ifndef CUB3D_H
# define CUB3D_H

# include "../libs/libft/libft.h"
# include "../libs/mlx/mlx.h"
# include "../libs/mlx/mlx_int.h"
# include <errno.h>
# include <fcntl.h>
# include <unistd.h>

# define DESTROY_HOOK 17
# define KEY_PRESSED_HOOK 2

# define KEY_ESCAPE 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100

# define KEY_ARROW_RIGHT 65563
# define KEY_ARROW_LEFT 65561

# define MAP_WALL 1
# define MAP_AIR 0

typedef struct s_player
{
    int x;
    int y;
}   t_player;

typedef struct s_map
{
    char **tiles;
    int width;
    int height;
}  t_map;

typedef struct s_game
{
    void        *mlx;
    void        *window;
    t_map       *map;
    t_player    *player;
}   t_game;

// Parser
int init_map(t_game *game);
int read_map(t_map *map);

// Utils
int init_game(t_game *game);

// Managers
void    init_listener(t_game *cub);

// Listeners
int    listen_exit(t_game *cub);
int listen_key_press(int keycode, t_game *cub);

void    clean(t_game *game);

#endif