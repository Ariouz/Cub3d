#include "../includes/cub3d.h"

int init_map(t_game *game)
{
    t_map   *map;   

    map = malloc(sizeof(t_map));
    map->height = 0;
    map->player_x = 0;
    map->player_y = 0;
    map->tiles = NULL;
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