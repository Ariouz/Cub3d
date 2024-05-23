/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicalvez <vicalvez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:22:36 by vicalvez          #+#    #+#             */
/*   Updated: 2024/05/23 17:01:09 by vicalvez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

unsigned int	get_pixel_img(t_img img, int x, int y)
{
	return (*(unsigned int *)((img.data
			+ (y * img.size_line) + (x * img.bpp / 8))));
}

void	put_pixel_img(t_img img, int x, int y, int color)
{
	char	*dst;

	if (color == (int) 0xFF000000)
		return ;
	if (x >= 0 && y >= 0 && x < img.width && y < img.height)
	{
		dst = img.data + (y * img.size_line + x * (img.bpp / 8));
		*(unsigned int *) dst = color;
	}
}

void	put_pixel_img_radius2(t_vector p_vec,
		t_vector vec, t_vector settings, t_img img)
{
	int		j;
	int		radius;
	int		color;
	char	*dst;

	radius = settings.ix;
	color = settings.iy;
	j = -radius / 2;
	while (j <= radius / 2)
	{
		p_vec.iy = vec.iy + j;
		if (p_vec.ix >= 0 && p_vec.iy >= 0 && p_vec.ix < img.width
			&& p_vec.iy < img.height)
		{
			dst = img.data + (int)(p_vec.iy * img.size_line + p_vec.ix
					* (img.bpp / 8));
			*(unsigned int *) dst = color;
		}
		j++;
	}
}

void	put_pixel_img_radius(t_img img, t_vector vec, int color, int radius)
{
	int			i;
	t_vector	p_vec;

	if (color == (int) 0xFF000000)
		return ;
	i = -radius / 2;
	while (i <= radius / 2)
	{
		p_vec.ix = vec.ix + i;
		put_pixel_img_radius2(p_vec, vec, vector(radius, color), img);
		i++;
	}
}

void	put_img_to_img(t_img *dst, t_img *src, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	while (i < (*src).width)
	{
		j = 0;
		while (j < (*src).height)
		{
			put_pixel_img(*dst, x + i, y + j, get_pixel_img(*src, i, j));
			j++;
		}
		i++;
	}
}
