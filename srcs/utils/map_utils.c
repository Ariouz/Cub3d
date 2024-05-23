/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicalvez <vicalvez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:05:33 by vicalvez          #+#    #+#             */
/*   Updated: 2024/05/23 17:05:43 by vicalvez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_player_tile(double player_pos)
{
	return (player_pos / TILE_SIZE);
}

int	get_tile_at(int x, int y, t_map *map)
{
	return (map->tiles[x + (y * map->width)]);
}
