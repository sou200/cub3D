/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serhouni <serhouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 11:01:00 by serhouni          #+#    #+#             */
/*   Updated: 2024/01/19 02:36:31 by serhouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void key_hook(void *param)
{
    t_data *data;

    data = (t_data *)param;
    if(mlx_is_key_down(data->mlx,  MLX_KEY_D))
        player_move(data, MOVE_RIGHT);
    if(mlx_is_key_down(data->mlx, MLX_KEY_A))
        player_move(data, MOVE_LEFT);
    if(mlx_is_key_down(data->mlx, MLX_KEY_W))
        player_move(data, MOVE_FORWARD);
    if(mlx_is_key_down(data->mlx, MLX_KEY_S))
        player_move(data, MOVE_BACKWARD);
    if(mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
        player_rotate_key(data, ROT_LEFT);
    if(mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
        player_rotate_key(data, ROT_RIGHT);
    if(mlx_is_key_down(data->mlx, MLX_KEY_EQUAL))
        data->minimap->zoom /= 0.9;
    if(mlx_is_key_down(data->mlx, MLX_KEY_MINUS))
        data->minimap->zoom *= 0.9;
    if(mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
        exit(0);
}