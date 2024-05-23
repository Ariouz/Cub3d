/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fog.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicalvez <vicalvez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:18:10 by vicalvez          #+#    #+#             */
/*   Updated: 2024/05/23 16:05:34 by vicalvez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mix_colors(t_color *c1, t_color *c2, double c2_factor)
{
	int	r;
	int	g;
	int	b;

	r = c1->r + c2_factor * (c2->r - c1->r);
	g = c1->g + c2_factor * (c2->g - c1->g);
	b = c1->b + c2_factor * (c2->b - c1->b);
	return ((r << 16) | (g << 8) | b);
}

t_color	get_color_struct(int rgb)
{
	t_color	color;

	color.r = (rgb >> 16) & 0xFF;
	color.g = (rgb >> 8) & 0xFF;
	color.b = rgb & 0xFF;
	return (color);
}

int	get_pixel_color_fog(t_raycast *ray, int color)
{
	double	max_distance;
	double	fog_factor;
	t_color	fog_color;
	t_color	px_color;

	max_distance = 12 * TILE_SIZE;
	fog_factor = ray->dist / max_distance;
	if (fog_factor > 1)
		fog_factor = 1;
	fog_color = get_color_struct(FOG_COLOR);
	px_color = get_color_struct(color);
	return (mix_colors(&px_color, &fog_color, fog_factor));
}
