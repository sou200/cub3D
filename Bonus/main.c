/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serhouni <serhouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 20:46:47 by serhouni          #+#    #+#             */
/*   Updated: 2024/01/25 20:47:22 by serhouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <string.h>

void	f(void)
{
	system("leaks cub3d");
}

int	main(int ac, char **av)
{
	t_data	*d;
	// atexit(f);

	d = game_init(ac, av);
	mlx_loop_hook(d->mlx, game_loop, d);
	mlx_loop_hook(d->mlx, key_hook, d);
	mlx_loop_hook(d->mlx, mouse_loop, d);
	mlx_close_hook(d->mlx, close_hook, d);
	mlx_mouse_hook(d->mlx, mouse_key_hook, d);
	mlx_set_cursor_mode(d->mlx, MLX_MOUSE_DISABLED);
	mlx_loop(d->mlx);
	terminate(d, EXIT_SUCCESS, NULL, 0);
}
