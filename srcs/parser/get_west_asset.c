/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_west_asset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gurousta <gurousta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 07:25:11 by gurousta          #+#    #+#             */
/*   Updated: 2024/05/23 16:03:36 by gurousta         ###   ########.fr       */
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

int	get_west_asset(t_game *game, t_assets *assets, char *line)
{
	int		h;
	int		w;
	size_t	index;
	size_t	size;
	char	*temp;

	index = 2;
	h = 0;
	w = 0;
	if (assets->west_wall != NULL)
		return (error_msg(game, MULTIPLE_FILE_TO_SAME_TEXTURE));
	while (line[index] == ' ')
		++index;
	if (line[index] == '\n' || line[index] == '\0')
		return (error_msg(game, WRONG_MAP_ARGUMENT));
	size = get_size(line + index);
	temp = ft_calloc(size + 1, sizeof(char));
	if (temp == NULL)
		return (error_msg(game, MALLOC_ERROR));
	ft_strlcpy(temp, line + index, size + 1);
	assets->west_wall = mlx_xpm_file_to_image(game->mlx, temp, &w, &h);
	free(temp);
	if (assets->west_wall == NULL)
		return (error_msg(game, MLX_FILE_TO_IMAGE_ERROR));
	return (0);
}
