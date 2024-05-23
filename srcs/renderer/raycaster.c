/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicalvez <vicalvez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:22:19 by vicalvez          #+#    #+#             */
/*   Updated: 2024/05/23 18:27:36 by vicalvez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	reset_ray(t_raycast *ray, t_player *player)
{
	ray->px = player->x;
	ray->py = player->y;
	ray->dis_h = 1000000;
	ray->hx = ray->px;
	ray->hy = ray->py;
	ray->dis_v = 1000000;
	ray->vx = ray->px;
	ray->vy = ray->py;
	ray->dist = 0;
}

void	ray_dist(t_raycast *ray, t_game *game, int *cardinal, int i)
{
	t_player	*player;

	player = game->player;
	if (ray->dis_v < ray->dis_h)
	{
		*cardinal = CARDINAL_WE;
		ray->rx = ray->vx;
		ray->ry = ray->vy;
		ray->dist = ray->dis_v;
		draw_walls(game, ray, player, vector(i, *cardinal));
	}
	if (ray->dis_h < ray->dis_v)
	{
		*cardinal = CARDINAL_NS;
		ray->rx = ray->hx;
		ray->ry = ray->hy;
		ray->dist = ray->dis_h;
		draw_walls(game, ray, player, vector(i, *cardinal));
	}
}

void	cast_rays(t_raycast *ray, t_game *game, int *cardinal)
{
	int			i;
	t_player	*player;
	t_map		*map;

	i = 0;
	player = game->player;
	map = game->map;
	while (i < 120)
	{
		reset_ray(ray, player);
		check_horizontal(map, ray);
		check_vertical(map, ray);
		ray_dist(ray, game, cardinal, i);
		ray->ra += DR / 2;
		ray->ra = fix_ang(ray->ra);
		i++;
	}
}

void	draw_rays(t_game *game)
{
	t_raycast	*ray;
	t_player	*player;
	t_map		*map;
	int			cardinal;
	int			i;

	ray = malloc(sizeof(t_raycast));
	if (!ray)
		return ;
	player = game->player;
	ray->ra = fix_ang(player->angle - to_radians(30));
	cardinal = CARDINAL_NS;
	map = game->map;
	i = 0;
	while (i < 120)
	{
		reset_ray(ray, player);
		check_horizontal(map, ray);
		check_vertical(map, ray);
		ray_dist(ray, game, &cardinal, i);
		ray->ra += DR / 2;
		ray->ra = fix_ang(ray->ra);
		i++;
	}
	free(ray);
}

void	draw_walls(t_game *game, t_raycast *ray, t_player *player,
	t_vector infos)
{
	t_vector	line_vec;
	t_vector	vars;
	t_vector	tex_vec;
	t_vector	tcoord;
	t_img		*texture;

	vars = vector(fix_ang(player->angle - ray->ra), 0);
	ray->dist *= cos(vars.dx);
	line_vec = vector((TILE_SIZE * game->win_height) / ray->dist, 0);
	tex_vec = vector (32 / line_vec.dx, 0);
	prevent_line_oversize(&line_vec, &tex_vec, game);
	line_vec.dy = game->win_height / 2 - (line_vec.dx / 2);
	draw_floor_ceil(vars, infos, line_vec, game);
	vars.dy = 0;
	tcoord.dy = (int) tex_vec.dy * tex_vec.dx;
	texture = get_texture(ray, infos, &tcoord, game);
	while (vars.dy < line_vec.dx)
	{
		put_pixel_img_radius(*game->cast_image, vector(infos.ix * 8, vars.dy
				+ line_vec.dy), get_pixel_color_fog(ray, get_pixel_img(*texture,
					tcoord.dx, tcoord.dy)), 8);
		vars.dy++;
		tcoord.dy += tex_vec.dx;
	}
}
