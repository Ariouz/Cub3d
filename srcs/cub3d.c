#include "../includes/cub3d.h"

void    clean(t_cub *cub)
{
    mlx_destroy_window(cub->mlx, cub->window);
    mlx_destroy_display(cub->mlx);
    free(cub);
}

int main(void)
{
    t_cub   *cub;

    cub = malloc(sizeof(t_cub));
    cub->mlx = NULL;
    cub->window = NULL;
    cub->mlx = mlx_init();

    if (cub->mlx == NULL)
    {
        free(cub);
        exit(1);
    }
    cub->window = mlx_new_window(cub->mlx, 960, 540, "cub3d");
    init_listener(cub);
    mlx_loop(cub->mlx);
    clean(cub);
    return (0);
}