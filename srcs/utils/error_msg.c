/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicalvez <vicalvez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:28:59 by gurousta          #+#    #+#             */
/*   Updated: 2024/05/23 16:15:01 by vicalvez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	error_open(t_game *game, char *file)
{
	write(1, "Error\n", 7);
	perror(file);
	return (1);
}

int	error_msg(t_game *game, char *err_msg)
{
	printf("Error\n%s", err_msg);
	exit(1);
	return (1);
}