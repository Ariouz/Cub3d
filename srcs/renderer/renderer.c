/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicalvez <vicalvez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:22:23 by vicalvez          #+#    #+#             */
/*   Updated: 2024/05/23 18:57:12 by vicalvez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_map(t_game *game, t_map *map)
{
	t_vector	vec;
	int			xo;
	int			yo;
	int			color;
	int			maps;

	vec = vector(0, 0);
	maps = TL_S;
	while (vec.iy < map->height)
	{
		while (vec.ix < map->width)
		{
			if (get_tile_at(vec.ix, vec.iy, map) == MAP_WALL)
				color = 0x111111;
			else
				color = 0x777777;
			xo = vec.ix * maps;
			yo = vec.iy * maps;
			draw_rect_to_img(game->cast_image, vector(xo, yo),
				vector(xo + maps, yo + maps), color);
			vec.ix++;
		}
		vec.ix = 0;
		vec.iy++;
	}
}

int	render_map(t_game *game)
{
	t_player	*player;

	player = game->player;
	move(game, game->player, game->keys);
	draw_rays(game);
	put_img_to_img(game->main_image, game->cast_image, 0, 0);
	draw_minimap(game, game->map, player);
	draw_line_to_img(game->main_image, vector(game->win_width / 2 - 7,
			game->win_height / 2), vector(game->win_width / 2 + 7,
			game->win_height / 2), 0xFFFFFF);
	draw_line_to_img(game->main_image, vector(game->win_width / 2,
			game->win_height / 2 - 7), vector(game->win_width / 2,
			game->win_height / 2 + 7), 0xFFFFFF);
	mlx_put_image_to_window(game->mlx, game->window, game->main_image, 0, 0);
	print_coords(game);
	show_tooltip(game);
	return (0);
}
