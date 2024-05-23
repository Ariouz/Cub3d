/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press_listener.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicalvez <vicalvez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 19:04:35 by vicalvez          #+#    #+#             */
/*   Updated: 2024/05/23 19:06:03 by vicalvez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_mouse_lock(t_game *game)
{
	game->mouse_lock = -game->mouse_lock;
	if (game->mouse_lock)
		mlx_mouse_hide(game->mlx, game->window);
	else
		mlx_mouse_show(game->mlx, game->window);
}

int	listen_key_press(int keycode, t_game *game)
{
	t_pressed_keys	*keys;

	keys = game->keys;
	if (keycode == KEY_ESCAPE)
		return (listen_exit(game));
	if (keycode == KEY_W)
		keys->w = 1;
	if (keycode == KEY_A)
		keys->a = 1;
	if (keycode == KEY_S)
		keys->s = 1;
	if (keycode == KEY_D)
		keys->d = 1;
	if (keycode == KEY_ARROW_LEFT)
		keys->la = 1;
	if (keycode == KEY_ARROW_RIGHT)
		keys->ra = 1;
	if (keycode == KEY_SPACE)
		handle_mouse_lock(game);
	return (0);
}

int	listen_key_release(int keycode, t_game *game)
{
	t_pressed_keys	*keys;

	keys = game->keys;
	if (keycode == KEY_ESCAPE)
		return (listen_exit(game));
	if (keycode == KEY_W)
		keys->w = 0;
	if (keycode == KEY_A)
		keys->a = 0;
	if (keycode == KEY_S)
		keys->s = 0;
	if (keycode == KEY_D)
		keys->d = 0;
	if (keycode == KEY_ARROW_LEFT)
		keys->la = 0;
	if (keycode == KEY_ARROW_RIGHT)
		keys->ra = 0;
	return (0);
}
