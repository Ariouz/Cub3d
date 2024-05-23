/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicalvez <vicalvez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 18:29:29 by vicalvez          #+#    #+#             */
/*   Updated: 2024/05/23 18:34:27 by vicalvez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    handle_rotation(t_player *player, t_pressed_keys *keys)
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

void    move_side(t_player *player, t_pressed_keys *keys, t_map *map)
{
    if (keys->a)
    {
        player->x += cos(player->angle - to_radians(90)) * PLAYER_SPEED;
        if (map->tiles[(int)((int)(player->y / TILE_SIZE) * map->width + (int)(player->x / TILE_SIZE))] == MAP_WALL)
            player->x += cos(player->angle + to_radians(90)) * PLAYER_SPEED;

        player->y += sin(player->angle - to_radians(90)) * PLAYER_SPEED;
        if (map->tiles[(int)((int)(player->y / TILE_SIZE) * map->width + (int)(player->x / TILE_SIZE))] == MAP_WALL)
            player->y += sin(player->angle + to_radians(90)) * PLAYER_SPEED;
    }

    if (keys->d)
    {
        player->x += cos(player->angle + to_radians(90)) * PLAYER_SPEED;
        if (map->tiles[(int)((int)(player->y/ TILE_SIZE) * map->width + (int)(player->x / TILE_SIZE))] == MAP_WALL)
            player->x += cos(player->angle - to_radians(90)) * PLAYER_SPEED;

        player->y += sin(player->angle + to_radians(90)) * PLAYER_SPEED;
        if (map->tiles[(int)((int)(player->y / TILE_SIZE) * map->width + (int)(player->x / TILE_SIZE))] == MAP_WALL)
            player->y += sin(player->angle - to_radians(90)) * PLAYER_SPEED;

    }
}

void    move(t_game *game, t_player *player, t_pressed_keys *keys)
{
    t_map *map;
    t_vector    o_vec;
    t_vector    i_vec;
    int ipx_add_xo;
    int ipx_sub_xo;
    int ipy_add_yo;
    int ipy_sub_yo;

    map = game->map;
    o_vec = vector(0, 0);
    if (player->dirX < 0)
        o_vec.ix = -20;
    else
        o_vec.ix = 20;
    if (player->dirY < 0)
        o_vec.iy = -20;
    else
        o_vec.iy = 20;
    i_vec = vector(player->x / TILE_SIZE, player->y / TILE_SIZE);
    ipx_add_xo = (player->x + o_vec.ix) / TILE_SIZE;
    ipx_sub_xo = (player->x - o_vec.ix) / TILE_SIZE;

    ipy_add_yo = (player->y + o_vec.iy) / TILE_SIZE;
    ipy_sub_yo = (player->y - o_vec.iy) / TILE_SIZE;

    if (keys->w)
    {
        if (map->tiles[i_vec.iy*map->width + ipx_add_xo] == 0)
            player->x += player->dirX;
        if (map->tiles[ipy_add_yo * map->width + i_vec.ix] == 0)
            player->y += player->dirY;
    }

    if (keys->s)
    {
        if (map->tiles[i_vec.iy*map->width + ipx_sub_xo] == 0)
            player->x -= player->dirX;
        if (map->tiles[ipy_sub_yo * map->width + i_vec.ix] == 0)
            player->y -= player->dirY;
    }
    
    move_side(player, keys, map);
    handle_rotation(player, keys);
}
