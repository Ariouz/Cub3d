/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gurousta <gurousta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:28:59 by gurousta          #+#    #+#             */
/*   Updated: 2024/05/23 17:06:17 by gurousta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	error_open(t_game *game, char *file)
{
	write(1, "Error\n", 7);
	perror(file);
	clean(game);
	return (1);
}

int	error_msg(t_game *game, char *err_msg)
{
	printf("Error\n%s", err_msg);
	clean(game);
	return (1);
}
