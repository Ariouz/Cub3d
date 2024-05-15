#include "../includes/cub3d.h"

void    init_listener(t_cub *cub)
{
    mlx_hook(cub->window, DESTROY_HOOK, 0, listen_exit, cub);
}