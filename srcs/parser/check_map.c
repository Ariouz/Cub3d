/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gurousta <gurousta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:40:14 by gurousta          #+#    #+#             */
/*   Updated: 2024/05/23 13:23:16 by gurousta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_map(t_game *game, char **map)
{
	if (check_element(game, map) != 0)
	{
		printf("check_element: did not pass\n");
		free_temp_map(map);
		return (1);
	}
	printf("check_element: pass\n");
	if (check_wall(map) != 0)
	{
		free_temp_map(map);
		printf("check_wall: did not pass\n");
		return (error_msg(game, MAP_DESCRIPTION_WALL_ERROR));
	}
	printf("check_wall: pass\n");
	exit(0);
	return (0);
}
