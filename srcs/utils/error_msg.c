/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicalvez <vicalvez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:28:59 by gurousta          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/05/23 16:30:37 by gurousta         ###   ########.fr       */
=======
/*   Updated: 2024/05/23 16:27:01 by vicalvez         ###   ########.fr       */
>>>>>>> 6100c37ebfd6bcc57400b5d6c2556163cea9d5b4
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
