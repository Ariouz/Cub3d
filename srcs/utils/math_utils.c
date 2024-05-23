/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicalvez <vicalvez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:22:58 by vicalvez          #+#    #+#             */
/*   Updated: 2024/05/23 17:05:58 by vicalvez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	to_radians(double degrees)
{
	return (degrees * (PI / 180));
}

double	to_degrees(double radians)
{
	return ((radians * 180) / PI);
}

double	center_pos(double pos)
{
	return (pos + (TILE_SIZE / 2));
}

double	dist(float ax, float ay, float bx, float by)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}
