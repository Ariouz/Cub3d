#ifndef CUB3D_H
# define CUB3D_H

# include "../libs/libft/libft.h"
# include "../libs/mlx/mlx.h"
# include "../libs/mlx/mlx_int.h"

# define DESTROY_HOOK 17
# define KEY_PRESSED_HOOK 2

typedef struct s_cub
{
    void    *mlx;
    void    *window;
}   t_cub;

// Managers
void    init_listener(t_cub *cub);

// Listeners
int    listen_exit(t_cub *cub);

#endif