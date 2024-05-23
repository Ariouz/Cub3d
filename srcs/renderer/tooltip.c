/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tooltip.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicalvez <vicalvez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:54:06 by vicalvez          #+#    #+#             */
/*   Updated: 2024/05/23 15:06:02 by vicalvez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    show_tooltip(t_game *game)
{
    char *mouse_lock;

    if (game->mouse_lock == 1)
        mouse_lock = ft_strdup("Press SPACE to disable mouse lock.");
    else    
        mouse_lock = ft_strdup("Press SPACE to enable mouse lock.");
    mlx_string_put(game->mlx, game->window, game->win_width / 2 - 90, game->win_height - 70, 0xFFFFFF, mouse_lock);
    free(mouse_lock);
}