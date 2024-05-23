/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicalvez <vicalvez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:25:16 by gurousta          #+#    #+#             */
/*   Updated: 2024/05/23 19:03:31 by vicalvez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (init_game(&game, argc - 1, argv + 1) != 0)
		return (EXIT_FAILURE);
	mlx_loop((&game)->mlx);
	clean(&game);
	return (0);
}
