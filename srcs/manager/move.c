/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicalvez <vicalvez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 18:29:29 by vicalvez          #+#    #+#             */
/*   Updated: 2024/05/23 18:52:35 by vicalvez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_frontward(t_map *map, t_player *player, t_vector add_vec,
	t_vector i_vec)
{
	if (map->tiles[i_vec.iy * map->width + add_vec.ix] == 0)
		player->x += player->dirX;
	if (map->tiles[add_vec.iy * map->width + i_vec.ix] == 0)
		player->y += player->dirY;
}

void	move_backward(t_map *map, t_player *player, t_vector sub_vec,
	t_vector i_vec)
{
	if (map->tiles[i_vec.iy * map->width + sub_vec.ix] == 0)
		player->x -= player->dirX;
	if (map->tiles[sub_vec.iy * map->width + i_vec.ix] == 0)
		player->y -= player->dirY;
}

void	move_player(t_pressed_keys *keys, t_map *map, t_player *player)
{
	move_side(player, keys, map);
	handle_rotation(player, keys);
}

void	move(t_game *game, t_player *pl, t_pressed_keys *keys)
{
	t_map		*map;
	t_vector	o_vec;
	t_vector	i_vec;
	t_vector	add_vec;
	t_vector	sub_vec;

	o_vec = vector(0, 0);
	if (pl->dirX < 0)
		o_vec.ix = -20;
	else
		o_vec.ix = 20;
	if (pl->dirY < 0)
		o_vec.iy = -20;
	else
		o_vec.iy = 20;
	i_vec = vector(pl->x / TL_S, pl->y / TL_S);
	add_vec = vector((pl->x + o_vec.ix) / TL_S, (pl->y + o_vec.iy) / TL_S);
	sub_vec = vector((pl->x - o_vec.ix) / TL_S, (pl->y - o_vec.iy) / TL_S);
	map = game->map;
	if (keys->w)
		move_frontward(map, pl, add_vec, i_vec);
	if (keys->s)
		move_backward(map, pl, sub_vec, i_vec);
	move_player(map, keys, pl);
}
