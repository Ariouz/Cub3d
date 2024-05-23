/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gurousta <gurousta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:22:26 by vicalvez          #+#    #+#             */
/*   Updated: 2024/05/23 15:17:45 by gurousta         ###   ########.fr       */
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
    if (read_map_temp(game, argv) != 0)
        return (1);
    return (0);
}
