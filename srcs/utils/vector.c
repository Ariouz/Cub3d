/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicalvez <vicalvez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:22:34 by vicalvez          #+#    #+#             */
/*   Updated: 2024/05/23 18:11:54 by vicalvez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_vector	vector(double x, double y)
{
	t_vector	vector;

	vector.ix = (int) x;
	vector.iy = (int) y;
	vector.dx = x;
	vector.dy = y;
	return (vector);
}

double	fix_ang(double a)
{
	if (a < 0)
		a += 2 * PI;
	if (a > 2 * PI)
		a -= 2 * PI;
	return (a);
}
