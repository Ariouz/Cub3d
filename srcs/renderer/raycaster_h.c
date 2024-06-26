/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_h.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicalvez <vicalvez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:44:36 by vicalvez          #+#    #+#             */
/*   Updated: 2024/05/23 18:50:57 by vicalvez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ray_dis_h(t_raycast *ray, t_map *map)
{
	while (ray->dof < 64)
	{
		ray->mx = (int) ray->rx / TL_S;
		ray->my = (int) ray->ry / TL_S;
		ray->mp = ray->my * map->width + ray->mx;
		if (ray->mp > 0 && ray->mp < map->width * map->height
			&& map->tiles[ray->mp] == MAP_WALL)
		{
			ray->dof = 64;
			ray->hx = ray->rx;
			ray->hy = ray->ry;
			ray->dis_h = dist(ray->px, ray->py, ray->hx, ray->hy);
		}
		else
		{
			ray->rx += ray->xo;
			ray->ry += ray->yo;
			ray->dof += 1;
		}
	}
}

void	check_horizontal(t_map *map, t_raycast *ray)
{
	ray->dof = 0;
	ray->atan = -1 / tan(ray->ra);
	if (ray->ra > PI)
	{
		ray->ry = (((int) ray->py / TL_S) * TL_S) - 0.0001;
		ray->rx = (ray->py - ray->ry) * ray->atan + ray->px;
		ray->yo = -TL_S;
		ray->xo = -ray->yo * ray->atan;
	}
	if (ray->ra < PI)
	{
		ray->ry = (((int) ray->py / TL_S) * TL_S) + TL_S;
		ray->rx = (ray->py - ray->ry) * ray->atan + ray->px;
		ray->yo = TL_S;
		ray->xo = -ray->yo * ray->atan;
	}
	if (ray->ra == 0 || ray->ra == PI)
	{
		ray->rx = ray->px;
		ray->ry = ray->py;
		ray->dof = 64;
	}
	ray_dis_h(ray, map);
}
