/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_element.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gurousta <gurousta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 12:17:11 by gurousta          #+#    #+#             */
/*   Updated: 2024/05/23 18:02:03 by gurousta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	compare_element(char c, int *position_found)
{
	if (c != '1' && c != '0' && c != 'N'
		&& c != 'S' && c != 'E' && c != 'W' && c != ' ')
		return (1);
	else if (c == 'S' || c == 'N' || c == 'E' || c == 'W')
		++(*position_found);
	return (0);
}

int	check_element(t_game *game, char **map)
{
	size_t	rows;
	size_t	cols;
	int		position_found;

	rows = 0;
	position_found = 0;
	while (map[rows])
	{
		cols = 0;
		while (map[rows][cols])
		{
			if (map[rows][cols] == '\n' && map[rows][cols + 1] == '\0')
				break ;
			if (compare_element(map[rows][cols], &position_found) != 0)
				return (error_msg(game, MAP_DESCRIPTION_ERROR));
			++cols;
		}
		++rows;
	}
	if (position_found != 1)
		return (error_msg(game, MAP_DESCRIPTION_PLAYER_ERROR));
	return (0);
}
