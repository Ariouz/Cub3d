/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicalvez <vicalvez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:22:08 by vicalvez          #+#    #+#             */
/*   Updated: 2024/05/23 19:39:19 by vicalvez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_coord(char *s, double coord)
{
	char	*itoa;
	char	*res;

	itoa = ft_itoa(coord);
	res = ft_strjoin(s, itoa);
	free(itoa);
	return (res);
}

char	*get_facing(int da)
{
	char	*facing;

	if (da >= 315 || (da >= 0 && da <= 45))
		facing = ft_strdup("Facing: East");
	else if (da > 45 && da <= 135)
		facing = ft_strdup("Facing: South");
	else if (da > 135 && da <= 270)
		facing = ft_strdup("Facing: West");
	else
		facing = ft_strdup("Facing: North");
	return (facing);
}

void	print_coords(t_game *game)
{
	char	*x;
	char	*y;
	char	*coords;
	char	*facing;
	int		da;

	x = get_coord("x: ", game->player->x);
	y = get_coord(" y: ", game->player->y);
	coords = ft_strjoin(x, y);
	free(x);
	free(y);
	mlx_string_put(game->mlx, game->window, game->win_width - MNMP_SLEN
		- 10, MNMP_SLEN + 25, 0xFFFFFF, coords);
	free(coords);
	da = to_degrees(game->player->angle);
	facing = get_facing(da);
	if (facing)
	{
		mlx_string_put(game->mlx, game->window, game->win_width
			- MNMP_SLEN - 10, MNMP_SLEN + 40, 0xFFFFFF, facing);
		free(facing);
	}
}

void	draw_minimap2(t_vector p_vec, t_vector *r_vec, t_vector m_vec,
		t_game *game)
{
	t_map		*map;
	t_vector	t_vec;
	int			color;
	int			radius;

	radius = -r_vec->iy;
	t_vec.ix = r_vec->ix;
	map = game->map;
	while (r_vec->iy < radius)
	{
		t_vec.iy = r_vec->iy;
		if (p_vec.iy + r_vec->iy < 0 || p_vec.iy + r_vec->iy >= map->height
			|| p_vec.ix + r_vec->ix < 0 || p_vec.ix + r_vec->ix >= map->width)
			color = 0x111111;
		else if (map->tiles[(p_vec.iy + r_vec->iy) * map->width + p_vec.ix
				+ r_vec->ix] == MAP_WALL)
			color = 0x222222;
		else
			color = 0x999999;
		draw_rect_to_img(game->main_image, vector(m_vec.ix
				+ (t_vec.ix * MN_TSIZE), m_vec.iy + (t_vec.iy * MN_TSIZE)),
			vector(m_vec.ix + (t_vec.ix * MN_TSIZE) + MN_TSIZE, m_vec.iy
				+ (t_vec.iy * MN_TSIZE) + MN_TSIZE), color);
		r_vec->iy++;
	}
}

void	draw_minimap(t_game *game, t_map *map, t_player *player)
{
	t_vector	c_vec;
	t_vector	m_vec;
	t_vector	r_vec;
	t_vector	p_vec;
	int			radius;

	(void) player;
	(void) map;
	c_vec = vector(game->win_width - MNMP_SLEN - 20, 10);
	draw_rect_to_img(game->main_image, vector(c_vec.ix, c_vec.iy),
		vector(c_vec.ix + MNMP_SLEN, c_vec.iy + MNMP_SLEN), 0xFF8c00);
	m_vec = vector(c_vec.ix + MNMP_SLEN / 2, c_vec.iy + MNMP_SLEN / 2);
	p_vec = vector(player->x / TL_S, player->y / TL_S);
	radius = 4;
	r_vec = vector(0, 0);
	r_vec.ix = -radius;
	while (r_vec.ix < radius)
	{
		r_vec.iy = -radius;
		draw_minimap2(p_vec, &r_vec, m_vec, game);
		r_vec.ix++;
	}
	draw_rect_to_img(game->main_image, vector(m_vec.ix - 2, m_vec.iy - 2),
		vector(m_vec.ix + 2, m_vec.iy + 2), 0xFFFFFF);
}
