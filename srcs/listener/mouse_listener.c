/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_listener.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicalvez <vicalvez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:31:22 by vicalvez          #+#    #+#             */
/*   Updated: 2024/05/23 15:15:27 by vicalvez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int listen_mousemove(int x, int y, t_game *game)
{
    (void) game;
    (void) y;
    t_player *player;

    if (game->mouse_lock == -1)
        return (0);
    player = game->player;
    if (player->mouseX < x)
    {
        player->angle += PLAYER_ROTATION_SPEED / 5;
        if (player->angle > 2 * PI)
            player->angle -= 2 * PI;
    }
    else
    {
        player->angle -= PLAYER_ROTATION_SPEED / 5;
        if (player->angle < 0)
            player->angle += 2 * PI;
    }
    player->dirX = cos(player->angle) * PLAYER_SPEED;
    player->dirY = sin(player->angle) * PLAYER_SPEED;
    player->mouseX = x;
    
    if (x <= 100 || x >= game->win_width - 100)
        mlx_mouse_move(game->mlx, game->window, game->win_width / 2, game->win_height / 2);
    return (0);
}