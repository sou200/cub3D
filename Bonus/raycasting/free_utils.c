/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serhouni <serhouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 14:43:07 by serhouni          #+#    #+#             */
/*   Updated: 2024/01/25 02:14:29 by serhouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_args(t_args *args, int free_map_f)
{
	if (free_map_f)
		free_2d(args->map);
	free(args->no);
	free(args->so);
	free(args->we);
	free(args->ea);
	free(args);
}

void	terminate(t_data *data, int exit_status, t_args *args, int free_args_f)
{
	if (free_args_f)
		free_args(args, 0);
	if (!data)
		return ;
	mlx_terminate(data->mlx);
	free_data(data);
	exit(exit_status);
}

void	close_hook(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	terminate(data, EXIT_SUCCESS, NULL, 0);
}
