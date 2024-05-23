/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicalvez <vicalvez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:22:33 by vicalvez          #+#    #+#             */
/*   Updated: 2024/05/23 16:42:48 by vicalvez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_line_to_img(t_img *img, t_vector v1, t_vector v2, int color)
{
	double	delta_x;
	double	delta_y;
	double	pixel_x;
	double	pixel_y;
	int		pixels;

	delta_x = v2.dx - v1.dx;
	delta_y = v2.dy - v1.dy;
	pixels = sqrt((delta_x * delta_x) + (delta_y * delta_y));
	delta_x /= pixels;
	delta_y /= pixels;
	pixel_x = v1.dx;
	pixel_y = v1.dy;
	while (pixels != 0)
	{
		put_pixel_img(*img, pixel_x, pixel_y, color);
		pixel_x += delta_x;
		pixel_y += delta_y;
		pixels--;
	}
}

void	draw_rect_to_img(t_img *img, t_vector v1, t_vector v2, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < v2.iy - v1.iy)
	{
		j = 0;
		while (j < v2.ix - v1.ix)
		{
			put_pixel_img(*img, j + v1.ix, i + v1.iy, color);
			j++;
		}
		i++;
	}
}
