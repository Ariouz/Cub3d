/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_listener.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicalvez <vicalvez@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:31:22 by vicalvez          #+#    #+#             */
/*   Updated: 2024/05/23 21:38:25 by vicalvez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	listen_mousemove(int x, int y, t_game *game)
{
	t_player	*player;

	(void) y;
	if (game->mouse_lock == -1)
		return (0);
	player = game->player;
	if (player->mousex < x)
		player->angle = fix_ang(player->angle + PLAYER_ROTATION_SPEED / 5);
	else
		player->angle = fix_ang(player->angle - PLAYER_ROTATION_SPEED / 5);
	player->dirx = cos(player->angle) * PLAYER_SPEED;
	player->diry = sin(player->angle) * PLAYER_SPEED;
	player->mousex = x;
	if (x <= 100 || x >= game->win_width - 100)
		mlx_mouse_move(game->mlx, game->window, game->win_width / 2,
			game->win_height / 2);
	return (0);
}
