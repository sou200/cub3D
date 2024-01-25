/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serhouni <serhouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 02:35:55 by serhouni          #+#    #+#             */
/*   Updated: 2024/01/25 04:51:11 by serhouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	mouse_key_hook(mouse_key_t button, action_t action, modifier_key_t mods,
		void *param)
{
	t_data	*data;

	(void)action;
	(void)mods;
	data = param;
	if (button == MLX_MOUSE_BUTTON_LEFT && !data->anim->anim_state)
	{
		data->anim->anim_state = 1;
		system("afplay rpg7e.mp3&");
	}
}

void	mouse_loop(void *param)
{
	int		dx;
	int		mouse_x;
	t_data	*data;

	data = param;
	mlx_get_mouse_pos(data->mlx, &mouse_x, &dx);
	dx = mouse_x - data->mouse_x;
	player_rotate(data, (dx / 5.0) * R_VOL);
	data->mouse_x = mouse_x;
}
