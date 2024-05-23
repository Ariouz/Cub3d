/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_floor_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gurousta <gurousta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 07:32:28 by gurousta          #+#    #+#             */
/*   Updated: 2024/05/23 13:17:15 by gurousta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	get_floor_color(t_game *game, t_assets *assets, char *line)
{
	size_t	index;
	
	index = 1;
	if (assets->floor_color != -1)
		return (error_msg(game, MULTIPLE_COLOR_TO_SAME_TEXTURE));
	while (line[index] == ' ')
		++index;
	if (line[index] == '\n' || line[index] == '\0')
		return (error_msg(game, WRONG_MAP_ARGUMENT));
	if (get_color(game, &assets->floor_color, line + index) != 0)
		return (1);
	printf("floor color = %d\n", assets->floor_color); // TO DELTE ONLY FOR TESTING
	return (0);
}
