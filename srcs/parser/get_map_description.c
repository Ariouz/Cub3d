/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_description.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gurousta <gurousta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 09:52:06 by gurousta          #+#    #+#             */
/*   Updated: 2024/05/23 18:01:33 by gurousta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static size_t	get_size_map(char **map, size_t index)
{
	size_t	count;

	count = 0;
	while (map[index] && map[index][0] != '\n')
	{
		--index;
		++count;
	}
	return (count);
}

char	**get_map_description(char **map)
{
	char	**map_description;
	size_t	size;
	size_t	index;

	index = 0;
	while (map[index] != NULL)
		++index;
	--index;
	size = get_size_map(map, index);
	map_description = ft_calloc(size + 1, sizeof(char *));
	if (map_description == NULL)
	{
		free_temp_map(map);
		return (NULL);
	}
	size = 0;
	while (map[index] && map[index][0] != '\n')
		--index;
	++index;
	while (map[index])
		map_description[size++] = ft_strdup(map[index++]);
	map_description[size] = NULL;
	free_temp_map(map);
	return (map_description);
}
