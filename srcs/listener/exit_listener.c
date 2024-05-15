#include "../includes/cub3d.h"

int    listen_exit(t_game *game)
{
    mlx_loop_end(game->mlx);
    return (0);
}