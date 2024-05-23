/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicalvez <vicalvez@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:22:39 by vicalvez          #+#    #+#             */
/*   Updated: 2024/05/23 21:36:45 by vicalvez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_value(t_game *game)
{
	game->win_width = 960;
	game->win_height = 640;
	game->mlx = NULL;
	game->window = NULL;
	game->map = NULL;
	game->player = NULL;
	game->keys = NULL;
	game->assets = NULL;
	game->cast_image = NULL;
	game->main_image = NULL;
	game->mouse_lock = -1;
}

int	init_player(t_game *game)
{
	t_player	*player;

	player = NULL;
	player = ft_calloc(1, sizeof(t_player));
	if (player == NULL)
		return (error_msg(game, MALLOC_ERROR));
	player->x = center_pos(game->map->player_x * TL_S);
	player->y = center_pos(game->map->player_y * TL_S);
	player->angle = to_radians(game->spawn_angle);
	player->dirx = cos(player->angle) * PLAYER_SPEED;
	player->diry = sin(player->angle) * PLAYER_SPEED;
	player->mousex = 0;
	game->player = player;
	return (0);
}

int	init_keys(t_game *game)
{
	t_pressed_keys	*keys;

	keys = NULL;
	keys = ft_calloc(1, sizeof(t_pressed_keys));
	if (keys == NULL)
		return (error_msg(game, MALLOC_ERROR));
	keys->w = 0;
	keys->a = 0;
	keys->s = 0;
	keys->d = 0;
	keys->la = 0;
	keys->ra = 0;
	game->keys = keys;
	return (0);
}

int	init_game(t_game *game, int argc, char **argv)
{
	init_value(game);
	if (argc != 1)
		return (error_msg(game, PARAMETER_NUMBER_ERROR));
	game->mlx = mlx_init();
	if (game->mlx == NULL)
		return (error_msg(game, MLX_INIT_ERROR));
	if (init_keys(game) != 0 || init_map(game, argv) != 0)
		return (1);
	if (init_player(game) != 0)
		return (1);
	game->main_image = mlx_new_image(game->mlx, game->win_width,
			game->win_height);
	if (game->main_image == NULL)
		return (error_msg(game, MLX_NEW_IMG_ERROR));
	game->cast_image = mlx_new_image(game->mlx, game->win_width,
			game->win_height);
	if (game->cast_image == NULL)
		return (error_msg(game, MLX_NEW_IMG_ERROR));
	game->window = mlx_new_window(game->mlx, game->win_width,
			game->win_height, "cub3d");
	if (game->window == NULL)
		return (error_msg(game, MLX_WINDOWS_INIT_ERROR));
	init_listener(game);
	mlx_loop_hook(game->mlx, render_map, game);
	return (0);
}
