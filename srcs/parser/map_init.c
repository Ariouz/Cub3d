/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicalvez <vicalvez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:22:26 by vicalvez          #+#    #+#             */
/*   Updated: 2024/05/23 16:10:19 by vicalvez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int init_map(t_game *game, char **argv)
{
    t_map   *map;   

    map = ft_calloc(1, sizeof(t_map));
    if (map == NULL)
        return (error_msg(game, MALLOC_ERROR));
    map->height = 0;
    map->player_x = 0;
    map->player_y = 0;
    map->size = 0;
    map->tiles = NULL;
    map->setting = NULL;
    game->map = map;
    if (read_map(game->map) != 0)
        return (1);
    return (0);
}
