/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serhouni <serhouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 11:01:00 by serhouni          #+#    #+#             */
/*   Updated: 2024/01/25 04:47:22 by serhouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	minimap_zoom(t_data *data, int zoom_in)
{
	if (zoom_in)
	{
		if (data->minimap->zoom * 0.9 < 0.01)
			data->minimap->zoom = 0.01;
		else
			data->minimap->zoom = data->minimap->zoom * 0.9;
	}
	else
	{
		if (data->minimap->zoom / 0.9 > 1.0)
			data->minimap->zoom = 1.0;
		else
			data->minimap->zoom = data->minimap->zoom / 0.9;
	}
}

void	key_hook(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		player_move(data, MOVE_RIGHT);
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		player_move(data, MOVE_LEFT);
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		player_move(data, MOVE_FORWARD);
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		player_move(data, MOVE_BACKWARD);
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		player_rotate_key(data, ROT_LEFT);
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		player_rotate_key(data, ROT_RIGHT);
	if (mlx_is_key_down(data->mlx, MLX_KEY_EQUAL))
		minimap_zoom(data, 1);
	if (mlx_is_key_down(data->mlx, MLX_KEY_MINUS))
		minimap_zoom(data, 0);
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		exit(0);
}
