/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gurousta <gurousta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 07:44:23 by gurousta          #+#    #+#             */
/*   Updated: 2024/05/23 18:00:26 by gurousta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	check_if_number(char *line)
{
	size_t	index;

	index = 0;
	if (ft_strlen(line) == 0)
		return (1);
	while (line[index] && line[index] != '\n')
	{
		if (line[index] >= '0' && line[index] <= '9')
			++index;
		else
		{
			free(line);
			return (1);
		}
	}
	return (0);
}

static int	get_color_value(t_game *game, char *line, size_t *index, int *color)
{
	char	*temp;
	size_t	index_temp;

	index_temp = *index;
	while (line[index_temp]
		&& line[index_temp] != ',' && line[index_temp] != '\n')
		++index_temp;
	temp = ft_calloc(index_temp - *index + 1, sizeof(char));
	if (temp == NULL)
		return (error_msg(game, MALLOC_ERROR));
	index_temp = 0;
	while (line[*index] && line[*index] != ',' && line[*index] != '\n')
		temp[index_temp++] = line[(*index)++];
	if (line[*index] == ',')
		++(*index);
	temp[index_temp] = '\0';
	if (check_if_number(temp) != 0)
		return (error_msg(game, WRONG_RGB_VALUE));
	*color = ft_atoi(temp);
	free(temp);
	if (*color < 0 || *color > 255)
		return (error_msg(game, WRONG_RGB_VALUE));
	return (0);
}

int	get_color(t_game *game, int *color, char *line)
{
	size_t	index;
	int		red;
	int		green;
	int		blue;

	index = 0;
	if (get_color_value(game, line, &index, &red) != 0)
		return (1);
	if (get_color_value(game, line, &index, &green) != 0)
		return (1);
	if (get_color_value(game, line, &index, &blue) != 0)
		return (1);
	*color = 256 * 256 * red + 256 * green + blue;
	return (0);
}
