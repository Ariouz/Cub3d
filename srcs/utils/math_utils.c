#include "cub3d.h"

double  to_radians(double degrees)
{
    return (degrees * (PI / 180));
}

double  to_degrees(double radians)
{
    return ((radians * 180) / PI);
}

int get_player_tile(double player_pos)
{
    return player_pos / TILE_SIZE;
}

int get_tile_at(int x, int y, t_map *map)
{
    return map->tiles[x + (y * map->width)];
}

double center_pos(double pos)
{
    return pos + (TILE_SIZE / 2);
}

double dist(float ax, float ay, float bx, float by)
{
    return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}