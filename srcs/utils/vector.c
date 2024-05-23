/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicalvez <vicalvez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:22:34 by vicalvez          #+#    #+#             */
/*   Updated: 2024/05/23 16:40:55 by vicalvez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

t_vector    vector(double x, double y)
{
    t_vector    vector;

    vector.ix = (int) x;
    vector.iy = (int) y;
    vector.dx = x;
    vector.dy = y;
    return (vector);
}