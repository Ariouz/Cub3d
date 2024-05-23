/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gurousta <gurousta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:22:29 by vicalvez          #+#    #+#             */
/*   Updated: 2024/05/23 15:27:01 by gurousta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

t_map_setting *read_map_settings(int fd)
{
    int s;
    char    *line;
    t_map_setting *setting;

    setting = malloc(sizeof(t_map_setting));
    fd = open("map.cub", O_RDONLY);
    if (fd == -1)
        return (0);

    line = get_next_line(fd);
    s = 0;
    setting->height = 0;
    while (line != NULL)
    {
        setting->width = ft_strlen(line);
        s += ft_strlen(line);
        setting->height++;
        free(line);
        line = get_next_line(fd);
    }
    setting->size = setting->height * setting->width;
    return (setting);
}

/*void print_map(t_map *map)
{
    int i;
    
    i = 0;
    while (i < map->height * map->width)
    {
        //printf("%d,", map->tiles[i]);
        fflush(NULL);
        if (i % map->width == map->width -1)
            printf("\n");
        i++;
    }
}*/

int read_map(t_map *map)
{
    int     fd;
    int     x;
    int     y;
    char    *line;
    int     *tiles;
    t_map_setting *setting;

    x = 0;
    fd = open("map.cub", O_RDONLY);
    if (fd == -1)
        return (1);
    setting = read_map_settings(fd);
    tiles = malloc(sizeof(int *) * (setting->size + 1));
    map->setting = setting;
    map->height = setting->height;
    map->width = setting->width;
    line = get_next_line(fd);
    y = 0;
    while (line != NULL)
    {
        x = 0;
        while (line[x] && line[x] != '\n')
        {
            if (ft_isalpha(line[x]))
            {
                map->player_x = x;
                map->player_y = y;
                tiles[y * map->width + x] = 0;
            }
            else
                tiles[y * map->width + x] = line[x] - '0';
            x++;
        }
        y++;
        free(line);
        line = get_next_line(fd);
    }
    tiles[y * map->width + x] = -1;
    map->tiles = tiles;
    close(fd);
    print_map(map);
    return (0);
}