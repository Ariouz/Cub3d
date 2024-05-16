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

int main(void)
{
    t_game   *game;

    game = malloc(sizeof(t_game));
    if (!game)
        exit(1);
    if (init_game(game) != 0)
        exit(1);
    mlx_loop(game->mlx);
    free_map(game->map);
    clean(game);
    return (0);
}