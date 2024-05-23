#include "../includes/cub3d.h"

int main(int argc, char **argv)
{
    t_game   game;

    if (init_game(&game, argc - 1, argv + 1) != 0)
        return (EXIT_FAILURE);
    mlx_loop((&game)->mlx);
    clean(&game);
    return (0);
}