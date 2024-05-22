/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_asset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gurousta <gurousta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:56:30 by gurousta          #+#    #+#             */
/*   Updated: 2024/05/22 18:39:46 by gurousta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static size_t	get_size(char *line)
{
	size_t	count;

	count = 0;
	while (line[count] && line[count] != ' ' && line[count] != '\n')
		++count;
	return (count);
}

static int	get_north_asset(t_game *game, t_assets *assets, char *line)
{
	int		h;
	int		w;
	size_t	index;
	size_t	size;
	char	*temp;

	index = 2;
	h = 0;
	w = 0;
	if (assets->north_wall != NULL)
		return (error_msg(game, MULTIPLE_FILE_TO_SAME_TEXTURE));
	while (line[index] == ' ')
		++index;
	if (line[index] == '\n' || line[index] == '\0')
		return (error_msg(game, WRONG_MAP_ARGUMENT));
	size = get_size(line + index);
	temp = ft_calloc(size, sizeof(char));
	if (temp == NULL)
		return (error_msg(game, MALLOC_ERROR));
	ft_strlcpy(temp, line + index, size);
	assets->north_wall = mlx_xpm_file_to_image(game->mlx, temp, &w, &h);
	free(temp);
	if (assets->north_wall == NULL)
		return (error_msg(game, MLX_FILE_TO_IMAGE_ERROR));
	return (0);
}

static int	check_line(t_game *game, t_assets *assets, char *line)
{
	if (ft_strncmp(line, "NO", 2) == 0)
		return (get_north_asset(game, assets, line));
	/*else if (ft_strncmp(line, "SO", 2) == 0)
		return (get_south_asset());
	else if (ft_strncmp(line, "WE", 2) == 0)
		return (get_west_asset());
	else if (ft_strncmp(line, "EA", 2) == 0)
		return (get_east_asset());
	else if (ft_strncmp(line, "F", 2) == 0)
		return (get_floor_asset());
	else if (ft_strncmp(line, "C", 2) == 0)
		return (get_ceiling_asset());
	else if (ft_strncmp(line, "\n", 1) == 0)
		return (0);*/
	else
		return (error_msg(game, WRONG_MAP_ARGUMENT));
	return (0);
}

int	get_asset(t_game *game, char **temp_map)
{
	t_assets	*assets;
	size_t		index;

	index = 0;
	assets = ft_calloc(1, sizeof(t_assets));
	if (assets == NULL)
	{
		free_temp_map(temp_map);
		return (error_msg(game, MALLOC_ERROR));
	}
	while (temp_map[index])
	{
		if (check_line(game, assets, temp_map[index++]) != 0)
		{
			free_temp_map(temp_map);
			return (1);
		}
	}
	game->assets = assets;
	return (0);
}
