#include "../includes/cub3d.h"

int read_map_height(int fd)
{
    int y;
    char    *line;

    fd = open("map.cub", O_RDONLY);
    if (fd == -1)
        return (0);

    line = get_next_line(fd);
    y = 0;
    while (line != NULL)
    {
        y++;
        free(line);
        line = get_next_line(fd);
    }
    return (y);
}

void    print_map(t_map *map)
{
    int i = 0;
    int x = 0;
    
    while (map->tiles[i] != 0)
    {
        while (map->tiles[i][x] >= 0)
        {
            //ft_printf("%d ", map->tiles[i][x]);
            x++;
        }
        x = 0;
        //ft_printf("\n");
        i++;
    }
}

int read_map(t_map *map)
{
    int     fd;
    int     x;
    int     y;
    int     i;
    char    *line;
    int     **tiles;

    x = 0;
    fd = open("map.cub", O_RDONLY);
    if (fd == -1)
        return (1);
    y = read_map_height(fd);
    if (y == 0)
        return (1);
    tiles = malloc(sizeof(int *) * (y + 1));
    map->height = y;
    i = 0;
    line = get_next_line(fd);
    while (line != NULL && line[0])
    {
        x = 0;
        tiles[i] = ft_calloc(ft_strlen(line) + 1, sizeof(int *));
        while (line[x])
        {
            if (ft_isalpha(line[x]))
            {
                map->player_x = x;
                map->player_y = i;
                tiles[i][x] = 0;
            }
            else
                tiles[i][x] = line[x] - '0';
            x++;
        }
        tiles[i][x] = -1;
        i++;
        free(line);
        line = get_next_line(fd);
    }
    tiles[i] = 0;
    map->tiles = tiles;
    close(fd);
    print_map(map);
    return (0);
}