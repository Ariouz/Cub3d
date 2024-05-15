#include "../includes/cub3d.h"

int    listen_exit(t_cub *cub)
{
    mlx_loop_end(cub->mlx);
    return (0);
}