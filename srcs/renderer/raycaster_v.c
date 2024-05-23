/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_v.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicalvez <vicalvez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:47:30 by vicalvez          #+#    #+#             */
/*   Updated: 2024/05/23 18:51:07 by vicalvez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ray_dis_v(t_raycast *ray, t_map *map)
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
			ray->vx = ray->rx;
			ray->vy = ray->ry;
			ray->dis_v = dist(ray->px, ray->py, ray->vx, ray->vy);
		}
		else
		{
			ray->rx += ray->xo;
			ray->ry += ray->yo;
			ray->dof += 1;
		}
	}
}

void	check_vertical(t_map *map, t_raycast *ray)
{
	ray->dof = 0;
	ray->atan = -tan(ray->ra);
	if (ray->ra > P2 && ray->ra < P3)
	{
		ray->rx = (((int) ray->px / TL_S) * TL_S) - 0.0001;
		ray->ry = (ray->px - ray->rx) * ray->atan + ray->py;
		ray->xo = -TL_S;
		ray->yo = -ray->xo * ray->atan;
	}
	if (ray->ra < P2 || ray->ra > P3)
	{
		ray->rx = (((int) ray->px / TL_S) * TL_S) + TL_S;
		ray->ry = (ray->px - ray->rx) * ray->atan + ray->py;
		ray->xo = TL_S;
		ray->yo = -ray->xo * ray->atan;
	}
	if (ray->ra == 0 || ray->ra == PI)
	{
		ray->rx = ray->px;
		ray->ry = ray->py;
		ray->dof = 64;
	}
	ray_dis_v(ray, map);
}
