#include "../includes/cub3d.h"

void    clean(t_game *game)
{
    mlx_destroy_window(game->mlx, game->window);
    mlx_destroy_display(game->mlx);
    free(game->mlx);
    free(game);
}

void    free_map(t_map *map)
{
    free(map->tiles);
    free(map);
}

int main(int argc, char **argv)
{
    t_game   game;

    if (init_game(&game, argc - 1, argv + 1) != 0)
        return (EXIT_FAILURE);
    mlx_loop((&game)->mlx);
    free_map((&game)->map);
    //clean(game);
    return (0);
}