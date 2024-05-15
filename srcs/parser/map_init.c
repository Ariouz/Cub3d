#include "../includes/cub3d.h"

int init_map(t_game *game)
{
    t_map   *map;   

    map = malloc(sizeof(t_map));
    if (!map)
        return (1);
    game->map = map;
    if (read_map(game->map) != 0)
    {   
        free(game->map);
        return (1);
    }
    return (0);
}