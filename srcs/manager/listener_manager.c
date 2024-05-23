/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listener_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicalvez <vicalvez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 19:03:54 by vicalvez          #+#    #+#             */
/*   Updated: 2024/05/23 19:04:13 by vicalvez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_listener(t_game *game)
{
	mlx_hook(game->window, DESTROY_HOOK, 0, listen_exit, game);
	mlx_hook(game->window, KEY_PRESSED_HOOK, (1L << 0), listen_key_press,
		game);
	mlx_hook(game->window, KEY_RELEASE_HOOK, (1L << 1), listen_key_release,
		game);
	mlx_hook(game->window, MOUSE_MOVE_HOOK, (1L << 6), listen_mousemove,
		game);
}
