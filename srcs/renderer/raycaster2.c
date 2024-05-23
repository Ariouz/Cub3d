/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicalvez <vicalvez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 18:26:06 by vicalvez          #+#    #+#             */
/*   Updated: 2024/05/23 18:26:27 by vicalvez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img	*get_texture(t_raycast *ray, t_vector infos, t_vector *tcoord,
	t_game *game)
{
	t_img	*texture;

	if (infos.iy == CARDINAL_NS)
	{
		tcoord->dx = (int)(ray->rx / 2) % 32;
		texture = game->assets->north_wall;
		if (to_degrees(ray->ra) > 180)
		{
			tcoord->dx = 31 - tcoord->dx;
			texture = game->assets->south_wall;
		}
	}
	else
	{
		tcoord->dx = (int)(ray->ry / 2) % 32;
		texture = game->assets->east_wall;
		if (to_degrees(ray->ra) > 90 && to_degrees(ray->ra) < 270)
		{
			texture = game->assets->west_wall;
			tcoord->dx = 31 - tcoord->dx;
		}
	}
	return (texture);
}

void	draw_floor_ceil(t_vector vars, t_vector infos, t_vector line_vec,
	t_game *game)
{
	vars.dy = line_vec.dy + line_vec.dx;
	while (vars.dy < game->win_height)
	{
		put_pixel_img_radius(*game->cast_image, vector(infos.ix * 8, vars.dy),
			game->assets->floor_color, 8);
		put_pixel_img_radius(*game->cast_image, vector(infos.ix * 8,
				game->win_height - vars.dy - 8), game->assets->ceil_color, 8);
		vars.dy++;
	}
}

void	prevent_line_oversize(t_vector *line_vec, t_vector *tex_vec,
	t_game *game)
{
	if (line_vec->dx > game->win_height)
	{
		tex_vec->dy = (line_vec->dx - game->win_height) / 2;
		line_vec->dx = game->win_height;
	}
}
