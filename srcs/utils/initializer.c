#include "../includes/cub3d.h"

int init_game(t_game *game)
{
    
    game->mlx = NULL;
    game->window = NULL;
    game->map = NULL;
    game->mlx = mlx_init();

    if (game->mlx == NULL)
    {
        free(game);
        return (1);
    }
    game->window = mlx_new_window(game->mlx, 960, 540, "cub3d");
    init_listener(game);
    if (init_map(game) != 0)
    {
        clean(game);
        return (1);
    }
    
    return (0);
}