/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serhouni <serhouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 02:35:55 by serhouni          #+#    #+#             */
/*   Updated: 2024/01/20 14:49:21 by serhouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void mouse_key_hook(mouse_key_t button, action_t action, modifier_key_t mods, void* param)
{
    (void)action;
    (void)mods;
    t_data *data = param;
    if(button == MLX_MOUSE_BUTTON_LEFT && !data->anim->anim_state)
    {
            data->anim->anim_state = 1;
            system("afplay rpg7e.mp3&");
    }
}

void mouse_loop(void *param)
{
    t_data *data;
    data = param;

    int Dx;
    int mouseX;
    mlx_get_mouse_pos(data->mlx, &mouseX, NULL);
    Dx = mouseX - data->mouseX;
    player_rotate(data, (Dx / 5.0) * R_VOL);
    data->mouseX = mouseX;
}