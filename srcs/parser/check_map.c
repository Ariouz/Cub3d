/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gurousta <gurousta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:40:14 by gurousta          #+#    #+#             */
/*   Updated: 2024/05/23 16:02:39 by gurousta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_map(t_game *game, char **map)
{
	if (check_element(game, map) != 0)
	{
		free_temp_map(map);
		return (1);
	}
	if (check_wall(map) != 0)
	{
		free_temp_map(map);
		return (error_msg(game, MAP_DESCRIPTION_WALL_ERROR));
	}
	return (0);
}
