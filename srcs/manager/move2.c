/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicalvez <vicalvez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 18:52:39 by vicalvez          #+#    #+#             */
/*   Updated: 2024/05/23 18:52:48 by vicalvez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_rotation(t_player *player, t_pressed_keys *keys)
{
	if (keys->la)
	{
		player->angle -= PLAYER_ROTATION_SPEED;
		if (player->angle < 0)
			player->angle += 2 * PI;
		player->dirX = cos(player->angle) * PLAYER_SPEED;
		player->dirY = sin(player->angle) * PLAYER_SPEED;
	}
	if (keys->ra)
	{
		player->angle += PLAYER_ROTATION_SPEED;
		if (player->angle > 2 * PI)
			player->angle -= 2 * PI;
		player->dirX = cos(player->angle) * PLAYER_SPEED;
		player->dirY = sin(player->angle) * PLAYER_SPEED;
	}
}

void	move_side(t_player *player, t_pressed_keys *keys, t_map *map)
{
	if (keys->a)
	{
		player->x += cos(player->angle - to_radians(90)) * PLAYER_SPEED;
		if (map->tiles[(int)((int)(player->y / TL_S) * map->width
			+ (int)(player->x / TL_S))] == MAP_WALL)
			player->x += cos(player->angle + to_radians(90)) * PLAYER_SPEED;
		player->y += sin(player->angle - to_radians(90)) * PLAYER_SPEED;
		if (map->tiles[(int)((int)(player->y / TL_S) * map->width
			+ (int)(player->x / TL_S))] == MAP_WALL)
			player->y += sin(player->angle + to_radians(90)) * PLAYER_SPEED;
	}
	if (keys->d)
	{
		player->x += cos(player->angle + to_radians(90)) * PLAYER_SPEED;
		if (map->tiles[(int)((int)(player->y / TL_S) * map->width
			+ (int)(player->x / TL_S))] == MAP_WALL)
			player->x += cos(player->angle - to_radians(90)) * PLAYER_SPEED;
		player->y += sin(player->angle + to_radians(90)) * PLAYER_SPEED;
		if (map->tiles[(int)((int)(player->y / TL_S) * map->width
			+ (int)(player->x / TL_S))] == MAP_WALL)
			player->y += sin(player->angle - to_radians(90)) * PLAYER_SPEED;
	}
}
