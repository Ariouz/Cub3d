/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicalvez <vicalvez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:22:26 by vicalvez          #+#    #+#             */
/*   Updated: 2024/05/22 16:22:54 by vicalvez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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