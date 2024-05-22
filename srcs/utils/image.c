/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicalvez <vicalvez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:22:36 by vicalvez          #+#    #+#             */
/*   Updated: 2024/05/22 16:22:37 by vicalvez         ###   ########.fr       */
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

void	put_pixel_img_radius(t_img img, int x, int y, int color, int radius)
{
	char	*dst;
	int		i, j;
	int		r = radius / 2;

	if (color == (int) 0xFF000000)
		return;

	for (i = -r; i <= r; i++)
	{
		for (j = -r; j <= r; j++)
		{
			int px = x + i;
			int py = y + j;
			if (px >= 0 && py >= 0 && px < img.width && py < img.height)
			{
				dst = img.data + (py * img.size_line + px * (img.bpp / 8));
				*(unsigned int *) dst = color;
			}
		}
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